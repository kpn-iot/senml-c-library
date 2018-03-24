#include <senml_bool_actuator.h>
#include <senml_logging.h>

void SenMLBoolActuator::actuate(const void* value, int dataLength, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_BOOL || dataType == CBOR_TYPE_BOOL){
        this->set(*((bool*)value));
        if(this->callback){
            this->callback(*((bool*)value));
        }
    }
    else{
        log_debug("invalid type");
    }
}






