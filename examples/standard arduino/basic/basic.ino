#include <kpn_senml.h>

SenMLPack doc("device_name");

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    delay(1000);
    Serial.println("start");
}

void loop(){
    int val = 10;                                   //just give it some value
    SenMLFloatRecord rec(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, val);
    doc.add(&rec);                      
    doc.toJson(&Serial);                            //as text
    Serial.println();
    doc.toJson(&Serial, SENML_HEX);                 //in hex format (often used in communication with lora modems)
    Serial.println();
    Serial.println();
    delay(1000);
}
