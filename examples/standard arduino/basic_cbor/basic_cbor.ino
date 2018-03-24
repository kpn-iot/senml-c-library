#include <kpn_senml.h>
#include <PrintEx.h>

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
    int val = analogRead(A1);  
    SenMLFloatRecord rec("temp", SENML_UNIT_DEGREES_CELSIUS, val);
    doc.add(&rec);                      

    char buffer[50];   
    memset(buffer,0,sizeof(buffer));         
    GString str = buffer;               //Wrap the buffer in a GString, making it printable.
    PrintAdapter streamer = str;        //Convert a Print object to a Stream object.
    doc.toCbor(&streamer);              //render it as a raw binary data blob
    
    for(int i = 0; i < 50; i++){
        printHex(buffer[i]);
    }
    Serial.println();
    Serial.println();

    //memset(buffer,0,sizeof(buffer));         
    //doc.toCbor(&streamer, SENML_HEX);   //directly renering HEX values
    //Serial.println(buffer);
    delay(1000);
}
