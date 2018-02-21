#include <senml_binary_actuator.h>
#include <Base64.h>

void SenMLBinaryActuator::actuate(const char* value, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_DATA){
        if(this->callback){
            int len = strlen(value);
            int decodedLen = base64_dec_len((char*)value, len);
            char decoded[decodedLen];
            base64_decode(decoded, (char*)value, len); 

//TODO:
//NEEDS FIXING: the set method doesn't make a copy of the data structure.

            this->set((unsigned char*)decoded, decodedLen);
            this->callback((unsigned char*)decoded, decodedLen);
        }
    }
    else
        log_debug("bin data type expected");
}