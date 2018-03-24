#ifndef SENMLSTRINGRECORD
#define SENMLSTRINGRECORD

#include <senml_record_t.h>

class SenMLStringRecord: public SenMLRecordTemplate<String>
{
public:
    SenMLStringRecord(const char* name):  SenMLRecordTemplate(name){};
    SenMLStringRecord(const char* name, SenMLUnit unit):  SenMLRecordTemplate(name, unit){};
    SenMLStringRecord(const char* name, SenMLUnit unit, const char* value):  SenMLRecordTemplate(name, unit, value){};
    //~SenMLStringRecord(){};

    /*
    renders all the fields to json, without the starting and ending brackets.
    Inheriters can extend this function if they want to add extra fields to the json output
    */
    virtual void fieldsToJson();

    //renders all the fields to cbor format. renders all the fields of the object without the {}
    virtual void fieldsToCbor();

protected:

private:
};

#endif // SENMLSTRINGRECORD






