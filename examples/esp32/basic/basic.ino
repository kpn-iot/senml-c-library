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
