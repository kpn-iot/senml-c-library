#ifndef SENMLSTRINGRECORD
#define SENMLSTRINGRECORD

#include <senml_record_t.h>

class SenMLStringRecord: public SenMLRecordTemplate<String>
{
public:
    SenMLStringRecord(const char* name);
    SenMLStringRecord(const char* name, SenMLUnit unit);
    SenMLStringRecord(const char* name, SenMLUnit unit, const char* value):  SenMLRecordTemplate(name, unit, value){};
    //~SenMLStringRecord(){};

    /*
    renders all the fields to json, without the starting and ending brackets.
    Inheriters can extend this function if they want to add extra fields to the json output
    */
    void fieldsToJson(Stream *dest) override;

    //renders all the fields to cbor format. renders all the fields of the object without the {}
    void fieldsToCbor(Stream *dest) override;

protected:

private:
};

#endif // SENMLSTRINGRECORD