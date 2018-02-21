#include <senml_String_actuator.h>

void SenMLStringActuator::actuate(const char* value, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_STRING){
        if(this->callback){
            this->set(value);
            this->callback(value);
        }
    }
    else
        log_debug("str data type expected");
}