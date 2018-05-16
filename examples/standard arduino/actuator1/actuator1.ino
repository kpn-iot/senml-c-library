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
 * actuators for arduino devices
 */

#include <kpn_senml.h>


void setTemp(float value){
    Serial.print("set the temp of the boiler to ");
    Serial.println(value);
}

SenMLPack doc("device_name");
SenMLFloatActuator rec(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, setTemp);

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    doc.add(&rec);   
    delay(1000);
    Serial.println("start");
}

void loop(){
    const char* buffer = "[{\"n\":\"temperature\",\"u\":\"Cel\",\"v\":23.1}]";
    doc.fromJson(buffer);
    Serial.println();
    Serial.println("done");
    delay(1000);
}
