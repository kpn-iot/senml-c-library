#ifndef SENMLTIMED
#define SENMLTIMED

#include <senml_base.h> 
#include <senml_enums.h>

class SenMLRecord: public SenMLBase
{
public:
    SenMLRecord(const char* name);
    SenMLRecord(const char* name, SenMLUnit unit);
   // ~SenMLRecord(){};

    void toJson(Stream *dest) override;

    //returns the time assigned to this record.
    //note: the time is relative compared to the parent pack object.
    double getTime() {return this->_time;};

    //set the time. This has to be a unix epoch time.
    //when absolute is true (default behaviour), the time value will be made relative to the base time of the pack object, if it has a base time.
    bool setTime(double value, bool absolute = true);

    const char* getName(){ return this->_name.c_str();}

    void setName(const char* name){ this->_name = name; }

    SenMLUnit getUnit(){ return this->_unit;}

    void setUnit(SenMLUnit value){ this->_unit = value; }

    //This function is called by the root SenMLPack object to indicate that the object
    //should adjust it's time info relative to the new base time (if applicable)
    //doesn't do anything by default
    void adjustToBaseTime(double prev, double time);

    /*
    renders all the fields to json, without the starting and ending brackets.
    Inheriters can extend this function if they want to add extra fields to the json output
    */
    void fieldsToJson(Stream *dest) override;

protected:

    //called while parsing a senml message, when the parser found the value for an ActuatorListener
    virtual void actuate(const char* value, SenMLDataType dataType);

    //calculates the nr of fields that this record will produce.
    //The default implementation already adds 1 field for the value.
    int getFieldLength() override;

    //renders all the fields to cbor format. renders all the fields of the object without the {}
    void fieldsToCbor(Stream *dest) override;

private:
    double _time;
    String _name;
    SenMLUnit _unit;

    friend class ActuatorListener;
};

#endif // SENMLRECORD