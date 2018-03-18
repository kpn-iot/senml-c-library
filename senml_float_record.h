#ifndef SENMLFLOATRECORD
#define SENMLFLOATRECORD

#include <senml_record_t.h>

class SenMLFloatRecord: public SenMLRecordTemplate<float>
{
public:
    SenMLFloatRecord(const char* name);
    SenMLFloatRecord(const char* name, SenMLUnit unit);
    SenMLFloatRecord(const char* name, SenMLUnit unit, float value):  SenMLRecordTemplate(name, unit, value){};
    ~SenMLFloatRecord(){};

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

#endif // SENMLFLOATRECORD