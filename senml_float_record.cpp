#include <senml_float_record.h>
#include <senml_helpers.h>
#include <cbor.h>

SenMLFloatRecord::SenMLFloatRecord(const char* name): SenMLRecordTemplate(name)
{
}

SenMLFloatRecord::SenMLFloatRecord(const char* name, SenMLUnit unit): SenMLRecordTemplate(name, unit)
{
}

void SenMLFloatRecord::fieldsToJson()
{
    SenMLRecord::fieldsToJson();
    printText(",\"v\":", 5);
    printDouble(this->get(), 16);
}

void SenMLFloatRecord::fieldsToCbor()
{
    SenMLRecord::fieldsToCbor();
    cbor_serialize_int(SENML_CBOR_V_LABEL);
    cbor_serialize_double(this->get());
}