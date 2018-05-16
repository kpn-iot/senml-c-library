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
 * custom records example for arduino devices
 */

#include "coordinates_record.h"
#include <senml_helpers.h>

#define LATITUDE 1
#define LONGITUDE 2
#define ALTIDUDE 3

CoordinatesRecord::CoordinatesRecord(const char* name): SenMLRecord(name)
{
}

CoordinatesRecord::CoordinatesRecord(const char* name, SenMLUnit unit): SenMLRecord(name, unit)
{
}

bool CoordinatesRecord::set(double lat, double lon, double alt, double time) 
{
    this->_lat = lat;
    this->_lon = lon;
    this->_alt = alt;
    return this->setTime(time);
}


void CoordinatesRecord::fieldsToJson()
{
    this->fieldsToJsonFor(LATITUDE);
    printText("},", 2);

    printText("{", 1);
    this->fieldsToJsonFor(LONGITUDE);
    printText("},", 2);

    printText("{", 1);
    this->fieldsToJsonFor(ALTIDUDE);
}

void CoordinatesRecord::fieldsToJsonFor(char field)
{
    printText("\"n\":\"", 5);
    const char* name = this->getName();
    printText(name, strlen(name));

    switch (field)
    {
        case LATITUDE:  printText("_lat", 4); break;
        case LONGITUDE: printText("_lon", 4); break;
        case ALTIDUDE:  printText("_alt", 4); break;
        default: break;
    }

    printText("\"", 1);
    if(!isnan(this->getTime())){
        printText(",\"t\":", 5);
        printDouble(this->getTime(), 16);
    }
    
    printText(",\"u\":\"", 6);
    switch (field)
    {
        case LATITUDE:  printText("lat", 3); break;
        case LONGITUDE: printText("lon", 3); break;
        case ALTIDUDE:  printText("m", 1); break;
        default: break;
    }
    printText("\"", 1);
    
    printText(",\"v\":", 5);

    switch (field)
    {
        case LATITUDE:  printDouble(this->_lat, 5); break;
        case LONGITUDE: printDouble(this->_lon, 5); break;
        case ALTIDUDE:  printDouble(this->_alt, 5); break;
        default: break;
    }
}

int CoordinatesRecord::fieldsToCbor()
{
    int res = this->fieldsToCborFor(LATITUDE);

    res += cbor_serialize_map(this->getFieldLength());
    res += this->fieldsToCborFor(LONGITUDE);
    
    res += cbor_serialize_map(this->getFieldLength());
    res += this->fieldsToCborFor(ALTIDUDE);
    return res;
}

int CoordinatesRecord::fieldsToCborFor(char field)
{
    String name = this->getName();
    switch (field)
    {
        case LATITUDE:  name += "_lat"; break;
        case LONGITUDE: name += "_lon"; break;
        case ALTIDUDE:  name += "_alt"; break;
    }
    int res = cbor_serialize_int(SENML_CBOR_N_LABEL);
    res += cbor_serialize_unicode_string(name.c_str());

    double time = this->getTime();
    if(!isnan(time)){
        res += cbor_serialize_int(SENML_CBOR_T_LABEL);
        res += cbor_serialize_double(time);
    }
    
    const char * unit = NULL;
    switch (field)
    {
        case LATITUDE:  unit = KPN_SENML_LATTITUDE; break;
        case LONGITUDE: unit = KPN_SENML_LONGITUDE; break;
        case ALTIDUDE:  unit = KPN_SENML_ALTITUDE; break;
    }
    res += cbor_serialize_int(SENML_CBOR_U_LABEL);
    res += cbor_serialize_unicode_string(senml_units_names[this->getUnit()]);
    
    double value = 0;
    switch (field)
    {
        case LATITUDE:  value = this->_lat; break;
        case LONGITUDE: value = this->_lon; break;
        case ALTIDUDE:  value = this->_alt; break;
        default: break;
    }
    res += cbor_serialize_int(SENML_CBOR_V_LABEL);
    res += cbor_serialize_double(value);
    return res;
}