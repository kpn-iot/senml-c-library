/*  _  __  ____    _   _ 
 * | |/ / |  _ \  | \ | |
 * | ' /  | |_) | |  \| |
 * | . \  |  __/  | |\  |
 * |_|\_\ |_|     |_| \_|
 * 
 * (c) 2018 KPN
 * License: MIT license 
 * Author: Jan Bogaerts
 * 
 * cbor actuators for mbed devices
 */

#include "mbed.h"
#include <kpn_senml.h>

//example: [{-2:"gateway",0:"temp",1:"Cel",2:23.1}, {-2:"dev1",0:"distance",1:"m",2:1000}]
//cbor to input: 82A4216767617465776179006474656D70016343656C02FB403719999999999AA4216464657631006864697374616E636501616D021903E8

Serial pc(USBTX, USBRX);

void printData(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    pc.printf("\r\ndevice: ");
    pc.printf(device);
    pc.printf("\r\nrecord: ");
    pc.printf(record);
    pc.printf("\r\nvalue: ");
    switch (dataType)
    {
        case SENML_TYPE_NR:     pc.printf((char*)value);       pc.printf(", data type: double"); break;
        case SENML_TYPE_STRING: pc.printf((char*)value);       pc.printf(", data type: string"); break;
        case SENML_TYPE_BOOL:   pc.printf((char*)value);       pc.printf(", data type: bool");   break;
        case SENML_TYPE_DATA:   pc.printf((char*)value);       pc.printf(", data type: binary"); break;

        case CBOR_TYPE_UINT:    pc.printf("%i", *(uint64_t*)value);  pc.printf(", data type: uint");   break;
        case CBOR_TYPE_INT:     pc.printf("%i",*(int64_t*)value);    pc.printf(", data type: int");    break;
        case CBOR_TYPE_STRING:  pc.printf((char*)value);             pc.printf(", data type: string"); break;
        case CBOR_TYPE_FLOAT:   pc.printf("%i", *(float*)value);     pc.printf(", data type: float (printf doesn't support this type)");  break;
        case CBOR_TYPE_DOUBLE:  pc.printf("%i",*(double*)value);     pc.printf(", data type: double (printf doesn't support this type)"); break;
        case CBOR_TYPE_BOOL:    pc.printf("%i",*(bool*)value);       pc.printf(", data type: bool");   break;
        case CBOR_TYPE_DATA:    pc.printf((char*)value);    pc.printf(", data type: data"); break;
    }
    pc.printf(", length: "); pc.printf("%i \r\n", valueLength); 
} 

void onActuator(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    pc.printf("for gateway");
    printData(device, record, value, valueLength, dataType);
}

void onActuator2(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    pc.printf("for nested");
    printData(device, record, value, valueLength, dataType);
}

SenMLPack gateway(onActuator);
SenMLPack device("dev1", onActuator2);


//use an interrupt callback so we only start to parse when data is available.
//the Serial.readable() function behaves funky and returns 1 even if there is no char available.
void serialDataCallback() {
    gateway.fromCbor(&pc, SENML_HEX);               //will block until a full message has arrived.
    pc.printf("done \r\n \r\n");
}

int main() {
    senMLSetLogger(&pc);
    gateway.add(&device);
    pc.printf("start\r\n");
    pc.attach(&serialDataCallback);  // attach pc ISR
    while(1) {

    }
}
