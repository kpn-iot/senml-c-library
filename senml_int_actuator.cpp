#include <senml_int_actuator.h>

void SenMLIntActuator::actuate(const char* value, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_NR){
        if(this->callback){
            int dVal = atoi(value);
            this->set(dVal);
            this->callback(dVal);
        }
    }
    else
        log_debug("nr data type expected");
}