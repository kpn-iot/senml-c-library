
#include <senml_double_pack.h> 
#include <senml_helpers.h>
#include <cbor.h> 


void SenMLDoublePack::setupStreamCtx(Stream *dest, SenMLStreamMethod format)
{
    SenMLPack::setupStreamCtx(dest, format);
    _streamCtx->baseValue.baseDouble = this->getBaseValue();
    _streamCtx->baseSum.baseDouble = this->getBaseValue();
    _streamCtx->baseDataType = CBOR_TYPE_DOUBLE;
}

void SenMLDoublePack::setupStreamCtx(char *dest, int length, SenMLStreamMethod format)
{
    SenMLPack::setupStreamCtx(dest, length, format);
    _streamCtx->baseValue.baseDouble = this->getBaseValue();
    _streamCtx->baseSum.baseDouble = this->getBaseValue();
    _streamCtx->baseDataType = CBOR_TYPE_DOUBLE;
}

void SenMLDoublePack::fieldsToJson() 
{
    double val;
    SenMLPack::fieldsToJson();
    val = this->getBaseValue();
    if(val != 0){
        printText(",\"bv\":", 6);
        printDouble(val, SENML_MAX_DOUBLE_PRECISION);
    }

    val = this->getBaseSum();
    if(val != 0){
        printText(",\"bs\":", 6);
        printDouble(val, SENML_MAX_DOUBLE_PRECISION);
    }

}

void SenMLDoublePack::fieldsToCbor() 
{
    int val;
    SenMLPack::fieldsToCbor();
    
    val = this->getBaseValue();
    if(val){
        cbor_serialize_int(SENML_CBOR_VB_LABEL);
        cbor_serialize_double(val);
    }

    val = this->getBaseSum();
    if(val){
        cbor_serialize_int(SENML_CBOR_BS_LABEL);
        cbor_serialize_double(val);
    }
}






