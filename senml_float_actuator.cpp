#include <senml_float_actuator.h>
#include <senml_logging.h>

void SenMLFloatActuator::actuate(const char* value, int dataLength, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_NR){
        if(this->callback){
            double dVal = atof(value);
            this->set(dVal);
            this->callback(dVal);
        }
    }
    else if(dataType == CBOR_TYPE_DOUBLE){
        this->set((double)*value);
        this->callback((double)*value);
    }
    else if(dataType == CBOR_TYPE_FLOAT){
        this->set((float)*value);
        this->callback((float)*value);
    }
    else
        log_debug("nr data type expected");
}