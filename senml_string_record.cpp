#include <senml_string_record.h>
#include <cbor.h>

void SenMLStringRecord::fieldsToJson(Stream *dest)
{
    SenMLRecord::fieldsToJson(dest);
    dest->print(",\"vs\":\"");
    dest->print(this->get());
    dest->print("\"");
}
void SenMLStringRecord::fieldsToCbor(Stream *dest)
{
    SenMLRecord::fieldsToCbor(dest);
    cbor_serialize_int(dest, SENML_CBOR_VS_LABEL);
    cbor_serialize_unicode_string(dest, this->get().c_str());
}