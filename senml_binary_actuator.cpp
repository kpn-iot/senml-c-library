#include <senml_binary_actuator.h>

#ifdef ESP32
extern "C" {
#include "libb64/cdecode.h"
}
int base64_dec_len(char * input, int inputLen) {
	int i = 0;
	int numEq = 0;
	for(i = inputLen - 1; input[i] == '='; i--) {
		numEq++;
	}

	return ((6 * inputLen) / 8) - numEq;
}

#else
#include <Base64.h>
#endif

void SenMLBinaryActuator::actuate(const char* value, SenMLDataType dataType)
{
    if(dataType == SENML_TYPE_DATA){
        if(this->callback){
            int len = strlen(value);
            int decodedLen = base64_dec_len((char*)value, len);
            char decoded[decodedLen];
            #ifdef ESP32
                base64_decode_chars(value, len, decoded);
            #else
               base64_decode(decoded, (char*)value, len); 
            #endif 

            this->set((unsigned char*)decoded, decodedLen);
            this->callback((unsigned char*)decoded, decodedLen);
        }
    }
    else
        log_debug("bin data type expected");
}