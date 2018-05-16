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
 * custom records for mbed devices
 */

#include "mbed.h"
#include <kpn_senml.h>
#include "coordinates_record.h"

Serial pc(USBTX, USBRX);
SenMLPack doc("device_name");

int main() {
    senMLSetLogger(&pc);
    while(1) {
        CoordinatesRecord rec("location");
        doc.add(&rec);                      
        rec.set(5.13, 30.1, 100.1);
        doc.toJson(&pc);
        pc.printf("done \r\n \r\n");
        wait(1);
    }
}
