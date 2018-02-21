#include <senml_bool_actuator.h>

void SenMLBoolActuator::actuate(const char* value, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_BOOL){
        if(this->callback){
            bool bVal = (strcmp (value,"true") == 0);
            this->set(bVal);
            this->callback(bVal);
        }
    }
    else
        log_debug("bool data type expected");
}