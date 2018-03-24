#include <kpn_senml.h>
#include <PrintEx.h>


void setTemp(float value){
    Serial.print("set the temp of the boiler to ");
    Serial.println(value);
}

SenMLPack doc("device_name");
SenMLFloatActuator rec("temp", SENML_UNIT_DEGREES_CELSIUS, setTemp);

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    doc.add(&rec);   
    delay(1000);
    Serial.println("start");
}

void loop(){
    const char* buffer = "[{\"n\":\"temp\",\"u\":\"Cel\",\"v\":23.1}]";
    doc.fromJson(buffer);
    Serial.println();
    Serial.println("done");
    delay(1000);
}
