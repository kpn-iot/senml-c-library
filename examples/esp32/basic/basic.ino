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
 * basic usage for esp32 devices
 */

#include <kpn_senml.h>

SenMLPack doc("device_name");

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    delay(1000);
    Serial.println("start");
}

void loop(){
    //int val = analogRead(A1);  
    SenMLFloatRecord rec("temp", SENML_UNIT_DEGREES_CELSIUS, 18.1);
    doc.add(&rec);                      
    doc.toJson(&Serial);
    Serial.println();
    delay(1000);
}
