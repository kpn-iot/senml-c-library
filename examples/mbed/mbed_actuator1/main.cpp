#include "mbed.h"
#include <kpn_senml.h>

Serial pc(USBTX, USBRX);

void setTemp(int value){
    pc.printf("set the temp of the boiler to  %i \r\n", value);
}

SenMLPack doc("device_name");
SenMLIntActuator rec("temp", SENML_UNIT_DEGREES_CELSIUS, setTemp);

int main() {
    senMLSetLogger(&pc);
    doc.add(&rec);   
    pc.printf("start\r\n");
    while(1) {
        const char* buffer = "[{\"n\":\"temp\",\"u\":\"Cel\",\"v\":23}]";
        doc.fromJson(buffer);
        pc.printf("done \r\n \r\n");
        wait(1);
    }
}