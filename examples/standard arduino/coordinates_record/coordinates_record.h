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

#ifndef SENMLCOORDINATESRECORD
#define SENMLCOORDINATESRECORD

#include <kpn_senml.h>

class CoordinatesRecord: public SenMLRecord
{
public:
    CoordinatesRecord(const char* name);
    CoordinatesRecord(const char* name, SenMLUnit unit);
    ~CoordinatesRecord(){};


    /*set the coordinates.
    */
    bool set(double lat, double lon, double alt, double time = NAN);


protected:

    //override the conversion to json so that we can generate 3 records instead of 1.
    //at the level of the fields, not the entire json object. This way, it can also be inlined by
    //the pack object when it is the first item in the list.
    virtual void fieldsToJson();


    //we render 3 senml objects instead of 1, so let the cbor renderer know this.
    virtual int getArrayLength() { return 3; };

    //renders all the fields to cbor format. renders all the fields of the object without the {}
    virtual int fieldsToCbor();
    
private:
    double _lat; 
    double _lon;
    double _alt;

    //render the fields for a single coordinate value
    void fieldsToJsonFor(char field);

    int fieldsToCborFor(char field);
};

#endif // SENMLCOORDINATESRECORD