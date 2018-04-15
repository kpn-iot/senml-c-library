#include <kpn_senml.h>

SenMLPack doc("device_name");

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    delay(1000);
    Serial.println("start");
}

void loop(){
    int val = digitalRead(1);  
    SenMLBoolRecord rec(KPN_SENML_TEMPERATURE);
    rec.set(val > 0);
    doc.add(&rec);                      

    char buffer[120];   
    memset(buffer,0, sizeof(buffer));            
    doc.toJson(buffer, sizeof(buffer));
    Serial.println(buffer);
    memset(buffer,0,sizeof(buffer));  
    doc.toJson(buffer, sizeof(buffer), SENML_HEX);
    Serial.println(buffer);
    delay(1000);
}
