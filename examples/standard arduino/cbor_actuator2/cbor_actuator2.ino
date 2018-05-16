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
 * cbor actuator example for arduino devices
 */

#include <kpn_senml.h>

//example: [{-2:"gateway",0:"temp",1:"Cel",2:23.1}, {-2:"dev1",0:"distance",1:"m",2:1000}]
//cbor to input: 82A4216767617465776179006474656D70016343656C02FB403719999999999AA4216464657631006864697374616E636501616D021903E8

void onActuator(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    Serial.println("for gateway");
    printData(device, record, value, valueLength, dataType);
}

void onActuator2(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    Serial.println("for nested");
    printData(device, record, value, valueLength, dataType);
}

void printData(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    Serial.print("device: ");
    Serial.println(device);
    Serial.print("record: ");
    Serial.println(record);
    Serial.print("value: ");
    switch (dataType)
    {
        //if it were cbor data
        case CBOR_TYPE_UINT:    Serial.println((unsigned long)*(uint64_t*)value);  Serial.print("data type: uint");   break;
        case CBOR_TYPE_INT:     Serial.println((long)*(int64_t*)value);   Serial.print("data type: int");    break;
        case CBOR_TYPE_STRING:  Serial.println((char*)value);       Serial.print("data type: string"); break;
        case CBOR_TYPE_FLOAT:   Serial.println(*(float*)value);     Serial.print("data type: float");  break;
        case CBOR_TYPE_DOUBLE:  Serial.println(*(double*)value);    Serial.print("data type: double"); break;
        case CBOR_TYPE_BOOL:    Serial.println(*(bool*)value);      Serial.print("data type: bool");   break;
        case CBOR_TYPE_DATA:    Serial.println((char*)value);       Serial.print("data type: data"); break;
    }
    Serial.print(", length: "); Serial.println(valueLength); 
}

SenMLPack gateway(onActuator);
SenMLPack device("dev1", onActuator2);

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    gateway.add(&device);
    delay(1000);
    Serial.println("start");
}

void loop(){
    if(Serial.available()) {
        gateway.fromCbor(&Serial, SENML_HEX);
        Serial.println("done");
        Serial.println();
        delay(1000);
    }
}
