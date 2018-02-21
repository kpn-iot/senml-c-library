#ifndef SENMLINTRECORD
#define SENMLINTRECORD

#include <senml_record_t.h>

class SenMLIntRecord: public SenMLRecordTemplate<int>
{
public:
    SenMLIntRecord(const char* name);
    SenMLIntRecord(const char* name, SenMLUnit unit);
    SenMLIntRecord(const char* name, SenMLUnit unit, int value):  SenMLRecordTemplate(name, unit, value){};
    ~SenMLIntRecord(){};


    /*
    renders all the fields to json, without the starting and ending brackets.
    Inheriters can extend this function if they want to add extra fields to the json output
    */
    void fieldsToJson(Stream *dest) override;

protected:

    //renders all the fields to cbor format. renders all the fields of the object without the {}
    void fieldsToCbor(Stream *dest) override;

private:
};

#endif // SENMLINTRECORD