#include <senml_int_record.h>
#include <cbor.h>
#include <senml_helpers.h>

SenMLIntRecord::SenMLIntRecord(const char* name): SenMLRecordTemplate(name)
{
}

SenMLIntRecord::SenMLIntRecord(const char* name, SenMLUnit unit): SenMLRecordTemplate(name, unit)
{
}

void SenMLIntRecord::fieldsToJson()
{
    SenMLRecord::fieldsToJson();
    printText(",\"v\":", 5);
    #ifdef __MBED__
        char buf[10];
        sprintf(buf, "%d", this->get());
        String val = buf;
    #else
        String val(this->get());
    #endif
    printText(val.c_str(), val.length());
}
void SenMLIntRecord::fieldsToCbor()
{
    SenMLRecord::fieldsToCbor();
    cbor_serialize_int(SENML_CBOR_V_LABEL);
    cbor_serialize_int(this->get());
}