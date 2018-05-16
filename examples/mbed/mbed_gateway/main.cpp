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
 * gateway for mbed devices
 */

#include "mbed.h"
#include <kpn_senml.h>

Serial pc(USBTX, USBRX);
SenMLPack doc("gateway");
unsigned char blob[10];                 //used for rendering a binary field

int main() {
    senMLSetLogger(&pc);
    for(int i = 0; i < 10; i++)         //initialize the array with some random data.
        blob[i] = i + 1;
    pc.printf("start \n\r");
    while(1) {
        SenMLPack dev1("dev1");
        SenMLPack dev2("dev2");
        SenMLPack dev3("dev3");

        doc.add(&dev1);
        doc.add(&dev2);
        doc.add(&dev3);

        SenMLFloatRecord rec1(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, 20.12);
        dev1.add(&rec1);                      

        SenMLBinaryRecord rec2("blob");
        rec2.set(blob, 10);
        dev2.add(&rec2);  

        SenMLStringRecord rec3("text", SENML_UNIT_NONE, "working");
        dev3.add(&rec3);    
        SenMLBoolRecord rec4("bool_val", SENML_UNIT_NONE, false);
        dev3.add(&rec4);   

        //doc.toJson(&pc, SENML_HEX);
        doc.toJson(&pc);
        pc.printf("\n\r \n\r");
        wait(1);
    }
}
