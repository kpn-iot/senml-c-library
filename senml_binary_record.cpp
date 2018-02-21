#include <senml_binary_record.h>
#include <senml_helpers.h>
#include <cbor.h>

SenMLBinaryRecord::SenMLBinaryRecord(const char* name): SenMLRecord(name)
{
}

SenMLBinaryRecord::SenMLBinaryRecord(const char* name, SenMLUnit unit): SenMLRecord(name, unit)
{
}

bool SenMLBinaryRecord::set(unsigned char* value, unsigned int length, double time) 
{
    this->_value = (unsigned char*)malloc(length);
    memcpy(this->_value, value, length);
    this->_length = length;
    return this->setTime(time);
}


void SenMLBinaryRecord::fieldsToJson(Stream *dest)
{
    SenMLRecord::fieldsToJson(dest);
    dest->print(",\"vd\":\"");
    printBinaryAsBase64(this->_value, this->_length, dest);
    dest->print("\"");
}

void SenMLBinaryRecord::fieldsToCbor(Stream *dest)
{
    SenMLRecord::fieldsToCbor(dest);
    cbor_serialize_int(dest, SENML_CBOR_V_LABEL);
    cbor_serialize_byte_string(dest, (const char*)this->_value, this->_length);
}