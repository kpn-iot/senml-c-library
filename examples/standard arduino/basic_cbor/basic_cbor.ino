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
 * basic cbor example for arduino devices
 */


#include <kpn_senml.h>

SenMLPack doc("device_name");

void setup(){
    Serial.begin(57600);
    senMLSetLogger(&Serial);
    delay(1000);
    Serial.println("start");
}

void printHex(unsigned char hex)
{
  char hexTable[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
  Serial.print(hexTable[hex /16]);
  Serial.print(hexTable[hex % 16]);
  Serial.print(' ');
}

void loop(){
    int val = 10;//analogRead(A1);  
    SenMLFloatRecord rec(KPN_SENML_TEMPERATURE, SENML_UNIT_DEGREES_CELSIUS, val);
    doc.add(&rec);                      

    char buffer[80];   
    memset(buffer, 0, sizeof(buffer));         
    int len = doc.toCbor(buffer, 80);              //render it as a raw binary data blob
    
    for(int i = 0; i <= len; i++){
        printHex(buffer[i]);
    }
    Serial.println();

    memset(buffer, 0, sizeof(buffer));         
    doc.toCbor(buffer, 80, SENML_HEX);   //directly renering HEX values
    Serial.println(buffer);
    Serial.println();
    Serial.println();
    delay(1000);
}
