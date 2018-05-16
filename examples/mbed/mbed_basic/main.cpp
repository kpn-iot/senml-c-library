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
 * basic usage for mbed devices
 */

#include "mbed.h"
#include "kpn_senml.h"

Serial pc(USBTX, USBRX);
SenMLPack doc("device_name");
DigitalIn  mypin(p5);               // change this to the button on your board

int main() {
    // check mypin object is initialized and connected to a pin
    if(mypin.is_connected()) {
        printf("mypin is connected and initialized! \n\r");
    }
    
    // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
    mypin.mode(PullNone); 

    senMLSetLogger(&pc);
    pc.printf("start \n\r");
    
    while(1) {
        int val = mypin.read();
        SenMLFloatRecord rec(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, val);
        doc.add(&rec);                      
        
        doc.toJson(&pc);
        pc.printf("\n\r");
        
       /* char buffer[120];   
        memset(buffer,0, sizeof(buffer));            
        doc.toJson(buffer, sizeof(buffer));
        pc.printf(buffer);
        pc.printf("\n\r");
        
        memset(buffer,0,sizeof(buffer));  
        doc.toJson(buffer, sizeof(buffer), SENML_HEX);
        pc.printf(buffer);
        pc.printf("\n\r");
        */
        wait(1);
    }
}
