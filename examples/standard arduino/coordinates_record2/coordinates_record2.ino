#include <kpn_senml.h>
#include "coordinates_record2.h"

SenMLPack doc("device_name");

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    delay(1000);
    Serial.println("start");
}

void loop(){
    CoordinatesRecord rec("temp");
    doc.add(&rec);                      
    rec.set(5.13, 30.10, 100.10);
    doc.toJson(&Serial);
    Serial.println();
    delay(1000);
}
