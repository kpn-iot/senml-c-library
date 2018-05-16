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

#include "coordinates_record2.h"
#include <senml_helpers.h>

CoordinatesRecord::CoordinatesRecord(const char* name): CoordinatesRecord(name, SENML_UNIT_NONE)
{
}

CoordinatesRecord::CoordinatesRecord(const char* name, SenMLUnit unit): SenMLRecord(name, unit), 
                                                        _lat(name, SENML_UNIT_DEGREES_LATITUDE),
                                                        _lon(name, SENML_UNIT_DEGREES_LONGITUDE),
                                                        _alt(name, SENML_UNIT_METER)
{
}

bool CoordinatesRecord::set(double lat, double lon, double alt, double time) 
{
    this->_lat.set(lat);
    this->_lon.set(lon);
    this->_alt.set(alt);
    return this->setTime(time);
}


void CoordinatesRecord::fieldsToJson()
{
    String name = this->getName();
    name += "_lat";
    this->_lat.setName(name.c_str());
    this->_lat.setTime(this->getTime());
    this->_lat.fieldsToJson();
    printText("},", 2);

    name = this->getName();
    name += "_lon";
    this->_lon.setName(name.c_str());
    this->_lon.setTime(this->getTime());
    printText("{", 1);
    this->_lon.fieldsToJson();
    printText("},", 2);

    name = this->getName();
    name += "_alt";
    this->_alt.setName(name.c_str());
    this->_alt.setTime(this->getTime());
    printText("{", 1);
    this->_alt.fieldsToJson();
}

int CoordinatesRecord::fieldsToCbor()
{
    String name = this->getName();
    name += "_lat";
    this->_lat.setName(name.c_str());
    this->_lat.setTime(this->getTime());
    int res = this->_lat.fieldsToCbor();

    name = this->getName();
    name += "_lon";
    this->_lon.setName(name.c_str());
    this->_lon.setTime(this->getTime());
    res += this->_lon.contentToCbor();

    name = this->getName();
    name += "_alt";
    this->_alt.setName(name.c_str());
    this->_alt.setTime(this->getTime());
    res += this->_alt.contentToCbor();
    return res;
}
