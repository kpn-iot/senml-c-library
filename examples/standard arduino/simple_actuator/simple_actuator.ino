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
 *actuator example for arduino devices
 */

#include <kpn_senml.h>



void onActuator(const char* device, const char* record, const void* value, int dataLength, SenMLDataType dataType)
{
    Serial.print("device: ");
    Serial.println(device);
    Serial.print("record: ");
    Serial.println(record);
    Serial.print("value: ");
    //value is void* cause it also has to support cbor data, which provides the data in the correct type, and not always as a string
    switch (dataType)
    {
        case SENML_TYPE_NR:     Serial.println((double*)value);       Serial.println("data type: double"); break;
        case SENML_TYPE_STRING: Serial.println((const char*)value);   Serial.println("data type: string");break;
        case SENML_TYPE_BOOL:   Serial.println((bool*)value);         Serial.println("data type: bool");break;
        case SENML_TYPE_DATA:   Serial.println((const char*)value);   Serial.println("data type: binary");break;

    }
}

SenMLPack doc(onActuator);

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    delay(1000);
    Serial.println("start");
}

void loop(){
    const char* buffer = "[{\"n\":\"temp\",\"u\":\"Cel\",\"v\":23.1}]";
    doc.fromJson(buffer);
    Serial.println();

    const char* buffer2 = "[{\"bn\":\"dev1\",\"n\":\"temp\",\"u\":\"Cel\",\"v\":23.1}, {\"bn\":\"dev2\",\"n\":\"distance\",\"u\":\"m\",\"v\":100}]";
    doc.fromJson(buffer2);
    Serial.println();

    Serial.println("done");
    delay(1000);
}
