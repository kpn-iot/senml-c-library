#include <senml_String_actuator.h>
#include <senml_logging.h>

void SenMLStringActuator::actuate(const char* value, int dataLength, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_STRING){
        if(this->callback){
            this->set(value);
            this->callback(value);
        }
    }
    else if(dataType == CBOR_TYPE_STRING){
        this->set((char *)value);
        this->callback((char*)value);
    }
    else
        log_debug("str data type expected");
}