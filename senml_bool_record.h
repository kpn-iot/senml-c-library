#ifndef SENMLBOOLRECORD
#define SENMLBOOLRECORD

#include <senml_record_t.h>

class SenMLBoolRecord: public SenMLRecordTemplate<bool>
{
public:
    SenMLBoolRecord(const char* name);
    SenMLBoolRecord(const char* name, SenMLUnit unit);
    SenMLBoolRecord(const char* name, SenMLUnit unit, bool value):  SenMLRecordTemplate(name, unit, value){};
    ~SenMLBoolRecord(){};

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

#endif // SENMLBOOLRECORD