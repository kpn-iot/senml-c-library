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
 * actuators for mbed devices
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
        const char* buffer = "[{\"n\":\"temperature\",\"u\":\"Cel\",\"v\":23}]";
        doc.fromJson(buffer);
        pc.printf("done \r\n \r\n");
        wait(1);
    }
}
