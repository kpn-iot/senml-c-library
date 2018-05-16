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
 * cbor actuators for arduino devices
 */

#include <kpn_senml.h>


const char* d_type = "data type: ";

//example input:
//[{"bn":"gateway","n":"temp","u":"Cel","v":23.1}, {"bn":"dev1", "bv": 200, "n":"distance","u":"m","v":100}]
//distance becomes 300 cause base value is added to it.

void onActuator(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    Serial.println(F("for gateway"));
    printData(device, record, value, valueLength, dataType);
}

void onActuator2(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    Serial.println(F("for nested"));
    printData(device, record, value, valueLength, dataType);
}

void printData(const char* device, const char* record, const void* value, int valueLength, SenMLDataType dataType)
{
    Serial.print(F("device: "));
    Serial.println(device);
    Serial.print(F("record: "));
    Serial.println(record);
    Serial.print(F("value: "));
    if(dataType == SENML_TYPE_NR){                              //compiler doesn't like string construct in switch, so put it in an 'if'
        String tempStr(*((double*)value));                      //println doesn't support doubles, but can convert to string.
        Serial.println(tempStr);  
        Serial.print(d_type);  
        Serial.print(F("double")); 
    }
    else{
        switch (dataType)
        {
            case SENML_TYPE_STRING: Serial.println((char*)value);       Serial.print(d_type);  Serial.print(F("string")); break;
            case SENML_TYPE_BOOL:   Serial.println(*((bool*)value));    Serial.print(d_type);  Serial.print(F("bool"));   break;
            case SENML_TYPE_DATA:   Serial.println((char*)value);       Serial.print(d_type);  Serial.print(F("binary")); break;
        }
    }
    Serial.print(F(", length: ")); Serial.println(valueLength); 
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
        gateway.fromJson(&Serial);
        Serial.println("done");
        Serial.println();
        delay(1000);
    }
}
