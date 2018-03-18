#include <senml_bool_actuator.h>
#include <senml_logging.h>

void SenMLBoolActuator::actuate(const char* value, int dataLength, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_BOOL){
        if(this->callback){
            bool bVal = (strcmp (value,"true") == 0);
            this->set(bVal);
            this->callback(bVal);
        }
    }
    else if(dataType == CBOR_TYPE_BOOL){
        this->set((bool)*value);
        this->callback((bool)*value);
    }
    else{
        log_debug("bool data type expected");
    }
}