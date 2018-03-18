
#include <senml_double_pack.h> 
#include <senml_helpers.h>
#include <cbor.h> 

void SenMLDoublePack::adjustForBaseValue(void* value, SenMLDataType dataType)
{
    //note: a pack that contains doubles can't adjust the values of int records cause then the value can't be composed correctly again.
    switch (dataType)
    {
        case CBOR_TYPE_FLOAT:  *((float*)value) -= this->getBaseValue();    break;
        case CBOR_TYPE_DOUBLE: *((double*)value) -= this->getBaseValue();   break;
    }
}

void SenMLDoublePack::fieldsToJson() 
{
    double val;
    SenMLPack::fieldsToJson();
    val = this->getBaseValue();
    if(val != 0){
        printText(",\"bv\":", 6);
        printDouble(val, 16);
    }

    val = this->getBaseSum();
    if(val != 0){
        printText(",\"bs\":", 6);
        printDouble(val, 16);
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
        cbor_serialize_int(SENML_CBOR_VS_LABEL);
        cbor_serialize_double(val);
    }
}