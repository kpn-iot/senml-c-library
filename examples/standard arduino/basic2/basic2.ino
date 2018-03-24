#include <kpn_senml.h>

SenMLPack doc("deviId");
SenMLFloatRecord temperature("temp", SENML_UNIT_DEGREES_CELSIUS);
SenMLBoolRecord doorPos("doorPos");
SenMLStringRecord strVal("str val");


void setup(){
    Serial.begin(57600);
	senMLSetLogger(&Serial);
    doc.setBaseName("basename");
    doc.setBaseUnit(SENML_UNIT_EVENT_RATE_PER_SECOND);
    doc.setBaseTime(1.0);
    doc.add(&temperature);
    doc.add(&doorPos);
    doc.add(&strVal);
    Serial.println("Starting program");
}

void loop(){
    temperature.set(20, 2.0);
    doorPos.set(true);
    strVal.set("test");
    doc.toJson(&Serial);
    Serial.println();
    delay(1000);
}



