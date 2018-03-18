#include <senml_int_actuator.h>
#include <senml_logging.h>

void SenMLIntActuator::actuate(const char* value, int dataLength, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_NR){
        if(this->callback){
            int dVal = atoi(value);
            this->set(dVal);
            this->callback(dVal);
        }
    }
    else if(dataType == CBOR_TYPE_INT){
        this->set((int64_t)*value);
        this->callback((int64_t)*value);
    }
    else
        log_debug("nr data type expected");
}