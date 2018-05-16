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
 * actuators for mbed devices
 */

#include "mbed.h"
#include <kpn_senml.h>

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
        case SENML_TYPE_NR:     pc.printf((double*)value);       pc.printf(", data type: double (printf doesn't support this type)"); break;
        case SENML_TYPE_STRING: pc.printf((char*)value);         pc.printf(", data type: string"); break;
        case SENML_TYPE_BOOL:   pc.printf((bool*)value);         pc.printf(", data type: bool");   break;
        case SENML_TYPE_DATA:   pc.printf((char*)value);         pc.printf(", data type: binary"); break;

        case CBOR_TYPE_UINT:    pc.printf("%i", *(uint64_t*)value);  pc.printf(", data type: uint");   break;
        case CBOR_TYPE_INT:     pc.printf("%i",*(int64_t*)value);    pc.printf(", data type: int");    break;
        case CBOR_TYPE_STRING:  pc.printf((char*)value);             pc.printf(", data type: string"); break;
        case CBOR_TYPE_FLOAT:   pc.printf("%i", *(float*)value);     pc.printf(", data type: float (printf doesn't support this type)");  break;
        case CBOR_TYPE_DOUBLE:  pc.printf("%i",*(double*)value);     pc.printf(", data type: double (printf doesn't support this type)"); break;
        case CBOR_TYPE_BOOL:    pc.printf("%i",*(bool*)value);       pc.printf(", data type: bool");   break;
        case CBOR_TYPE_DATA:    pc.printf((char*)value);             pc.printf(", data type: data"); break;
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

int main() {
    senMLSetLogger(&pc);
    gateway.add(&device);
    pc.printf("start\r\n");
    while(1) {
        const char* buffer = "[{\"bn\":\"gateway\",\"n\":\"temp\",\"u\":\"Cel\",\"v\":23.1}, {\"bn\":\"dev1\",\"bv\":200,\"n\":\"distance\",\"u\":\"m\",\"v\":100}]";
        gateway.fromJson(buffer);
        pc.printf("done \r\n \r\n");
        wait(1);
    }
}
