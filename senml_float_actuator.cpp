#include <senml_float_actuator.h>

void SenMLFloatActuator::actuate(const char* value, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_NR){
        if(this->callback){
            double dVal = atof(value);
            this->set(dVal);
            this->callback(dVal);
        }
    }
    else
        log_debug("nr data type expected");
}