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


void setTemp(int value){
    Serial.print("set the temp of the boiler to ");
    Serial.println(value);
}

SenMLPack doc("device_name");
SenMLIntActuator rec("temp", SENML_UNIT_DEGREES_CELSIUS, setTemp);

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    doc.add(&rec);   
    delay(1000);
    Serial.println("start");
}

void loop(){
    char* input = "81A4216B6465766963655F6E616D65006474656D70016343656C0214";  //this represents the cbor json struct: [{-2: "device_name", 0: "temp", 1: "Cel", 2: 20}]
    doc.fromCbor(input, strlen(input), SENML_HEX);
    Serial.println();
    Serial.println("done");
    delay(1000);
}
