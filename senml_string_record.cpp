#include <senml_string_record.h>
#include <cbor.h>
#include <senml_helpers.h>

void SenMLStringRecord::fieldsToJson()
{
    SenMLRecord::fieldsToJson();
    printText(",\"vs\":\"", 7);
    String val = this->get();
    printText(val.c_str(), val.length());
    printText("\"", 1);
}
void SenMLStringRecord::fieldsToCbor()
{
    SenMLRecord::fieldsToCbor();
    cbor_serialize_int(SENML_CBOR_VS_LABEL);
    cbor_serialize_unicode_string(this->get().c_str());
}






