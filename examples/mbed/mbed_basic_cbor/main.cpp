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
 * cbor basic usage for mbed devices
 */

#include "mbed.h"
#include "kpn_senml.h"

Serial pc(USBTX, USBRX);
SenMLPack doc("device_name");


int main() {
    senMLSetLogger(&pc);
    pc.printf("start \n\r");
    while(1) { 
        SenMLFloatRecord rec(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, 20);
        doc.add(&rec);                      

        doc.toCbor(&pc);                        //render it as a raw binary data blob directly to stream
        pc.printf("\n\r \n\r");
        doc.toCbor(&pc, SENML_HEX);             //directly renering HEX values  directly to stream
        pc.printf("\n\r \n\r");

        char buffer[80];                        //directly renering HEX values to memory
        memset(buffer, 0, sizeof(buffer));  
        doc.toCbor(buffer, 80, SENML_HEX);   
        pc.printf(buffer);
        pc.printf("\n\r \n\r");
        wait(1);
    }
}
