#include <kpn_senml.h>

SenMLIntPack doc("device_name");
SenMLFloatRecord recFloat(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS);
SenMLIntRecord recInt(KPN_SENML_VOLUME, SENML_UNIT_CUBIC_METER);

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    doc.add(&recFloat);   
    doc.add(&recInt);   
    doc.setBaseValue(2);                   
    doc.setBaseSum(40);
    delay(1000);
    Serial.println("start");
}

void loop(){
    recFloat.set(10.0);
    recInt.set(100, (double)NAN, true);             //true indicates that it should be interpreted as a sum
    doc.toJson(&Serial);                            //as text
    Serial.println();
    delay(1000);
}
