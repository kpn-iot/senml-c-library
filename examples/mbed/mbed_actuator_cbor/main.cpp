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
 * cbor actuators for mbed devices
 */

#include "mbed.h"
#include <kpn_senml.h>

Serial pc(USBTX, USBRX);

void setTemp(int value){
    pc.printf("set the temp of the boiler to  %i \r\n", value);
}

SenMLPack doc("device_name");
SenMLIntActuator rec(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, setTemp);

int main() {
    senMLSetLogger(&pc);
    doc.add(&rec);   
    pc.printf("start\r\n");
    while(1) {
        char* input = "81A4216B6465766963655F6E616D65006474656D70016343656C0214";  //this represents the cbor json struct: [{-2: "device_name", 0: "temp", 1: "Cel", 2: 20}]
        doc.fromCbor(input, strlen(input), SENML_HEX);
        pc.printf("done \r\n \r\n");
        wait(1);
    }
}
