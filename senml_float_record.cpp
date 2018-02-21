#include <senml_float_record.h>
#include <senml_helpers.h>
#include <cbor.h>

SenMLFloatRecord::SenMLFloatRecord(const char* name): SenMLRecordTemplate(name)
{
}

SenMLFloatRecord::SenMLFloatRecord(const char* name, SenMLUnit unit): SenMLRecordTemplate(name, unit)
{
}

void SenMLFloatRecord::fieldsToJson(Stream *dest)
{
    SenMLRecord::fieldsToJson(dest);
    dest->print(",\"v\":");
    printDouble(this->get(), 16, dest);
}

void SenMLFloatRecord::fieldsToCbor(Stream *dest)
{
    SenMLRecord::fieldsToCbor(dest);
    cbor_serialize_int(dest, SENML_CBOR_V_LABEL);
    cbor_serialize_double(dest, this->get());
}