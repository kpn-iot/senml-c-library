#include <senml_int_record.h>
#include <cbor.h>
#include <senml_helpers.h>
#include <senml_int_pack.h> 

SenMLIntRecord::SenMLIntRecord(const char* name): SenMLRecordTemplate(name)
{
}

SenMLIntRecord::SenMLIntRecord(const char* name, SenMLUnit unit): SenMLRecordTemplate(name, unit)
{
}

int SenMLIntRecord::getAdjustedValue()
{
    int adjustedValue = this->get();
    if(_streamCtx->baseDataType == CBOR_TYPE_INT)
        adjustedValue -= ((SenMLIntPack*)this->getRoot())->getBaseValue();
    return adjustedValue;
}

void SenMLIntRecord::fieldsToJson()
{
    SenMLRecord::fieldsToJson();
    if(this->asSum())
        printText(",\"s\":", 5);
    else
        printText(",\"v\":", 5);
    #ifdef __MBED__
        char buf[10];
        sprintf(buf, "%d", this->getAdjustedValue());
        String val = buf;
    #else
        String val(this->getAdjustedValue());
    #endif
    printText(val.c_str(), val.length());
}


void SenMLIntRecord::fieldsToCbor()
{
    SenMLRecord::fieldsToCbor();
    if(this->asSum())
        cbor_serialize_int(SENML_CBOR_S_LABEL);
    else
        cbor_serialize_int(SENML_CBOR_V_LABEL);
    cbor_serialize_int(this->getAdjustedValue());
}






