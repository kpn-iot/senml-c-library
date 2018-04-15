#include "mbed.h"
#include "kpn_senml.h"

Serial pc(USBTX, USBRX);
SenMLPack doc("device_name");


int main() {
    senMLSetLogger(&pc);
    pc.printf("start \n\r");
    while(1) { 
        SenMLFloatRecord rec("temp", SENML_UNIT_DEGREES_CELSIUS, 20);
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
