#include "coordinates_record.h"
#include <senml_helpers.h>

CoordinatesRecord::CoordinatesRecord(const char* name): SenMLRecord(name, SENML_UNIT_NONE), 
                                                        _lat(name, SENML_UNIT_DEGREES_LATITUDE),
                                                        _lon(name, SENML_UNIT_DEGREES_LONGITUDE),
                                                        _alt(name, SENML_UNIT_METER)
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

void CoordinatesRecord::fieldsToCbor()
{
    String name = this->getName();
    name += "_lat";
    this->_lat.setName(name.c_str());
    this->_lat.setTime(this->getTime());
    this->_lat.fieldsToCbor();

    name = this->getName();
    name += "_lon";
    this->_lon.setName(name.c_str());
    this->_lon.setTime(this->getTime());
    this->_lon.contentToCbor();

    name = this->getName();
    name += "_alt";
    this->_alt.setName(name.c_str());
    this->_alt.setTime(this->getTime());
    this->_alt.contentToCbor();
}
