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
 * custom records example for arduino devices
 */

#include <kpn_senml.h>
#include "coordinates_record.h"

SenMLPack doc("device_name");

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    delay(1000);
    Serial.println("start");
}

void loop(){
    CoordinatesRecord rec("location");
    doc.add(&rec);                      
    rec.set(5.13, 30.1, 100.1);
    doc.toJson(&Serial);
    Serial.println();
    delay(1000);
}
