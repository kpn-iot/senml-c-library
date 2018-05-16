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
 * gateway example for arduino devices
 */

#include <kpn_senml.h>

SenMLPack doc("gateway");
unsigned char blob[10];                 //used for rendering a binary field


void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    for(int i = 0; i < 10; i++)         //initialize the array with some random data.
        blob[i] = i + 1;
    delay(1000);
    Serial.println("start");
}

void loop(){
    SenMLPack dev1("dev1");
    SenMLPack dev2("dev2");
    SenMLPack dev3("dev3");

    doc.add(&dev1);
    doc.add(&dev2);
    doc.add(&dev3);

    SenMLFloatRecord rec1(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, 20.0);
    dev1.add(&rec1);                      

    SenMLBinaryRecord rec2("blob");
    rec2.set(blob, 10);
    dev2.add(&rec2);  

    SenMLStringRecord rec3("text", SENML_UNIT_NONE, "working");
    dev3.add(&rec3);    
    SenMLBoolRecord rec4("bool_val", SENML_UNIT_NONE, false);
    dev3.add(&rec4);   

    doc.toJson(&Serial);                        //use doc.toJson(&Serial, SENML_HEX); for direct hex printing
    Serial.println();
    delay(1000);
}
