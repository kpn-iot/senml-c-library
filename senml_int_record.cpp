#include <senml_int_record.h>
#include <cbor.h>

SenMLIntRecord::SenMLIntRecord(const char* name): SenMLRecordTemplate(name)
{
}

SenMLIntRecord::SenMLIntRecord(const char* name, SenMLUnit unit): SenMLRecordTemplate(name, unit)
{
}

void SenMLIntRecord::fieldsToJson(Stream *dest)
{
    SenMLRecord::fieldsToJson(dest);
    dest->print(",\"v\":");
    dest->print(this->get());
}
void SenMLIntRecord::fieldsToCbor(Stream *dest)
{
    SenMLRecord::fieldsToCbor(dest);
    cbor_serialize_int(dest, SENML_CBOR_V_LABEL);
    cbor_serialize_int(dest, this->get());
}