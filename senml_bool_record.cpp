#include <senml_bool_record.h>
#include <cbor.h>

SenMLBoolRecord::SenMLBoolRecord(const char* name): SenMLRecordTemplate(name)
{
}

SenMLBoolRecord::SenMLBoolRecord(const char* name, SenMLUnit unit): SenMLRecordTemplate(name, unit)
{
}

void SenMLBoolRecord::fieldsToJson(Stream *dest)
{
    SenMLRecord::fieldsToJson(dest);
    dest->print(",\"vb\":");
    if(this->get())
        dest->print("true");
    else
        dest->print("false");
}

void SenMLBoolRecord::fieldsToCbor(Stream *dest)
{
    SenMLRecord::fieldsToCbor(dest);
    cbor_serialize_int(dest, SENML_CBOR_VB_LABEL);
    cbor_serialize_bool(dest, this->get());
}