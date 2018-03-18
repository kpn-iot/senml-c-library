#include <senml_cbor_parser.h>
#include <senml_helpers.h>
#include <senml_binary_actuator.h>

void SenMLCborParser::parse()
{
    _streamCtx = &this->ctx;                                     //set the global variable so that we don't have to pass it along on the stack all the time (saves mem & codesize)
    while (peekChar() > -1) {
        unsigned int read_bytes = this->parseNext();

        if (read_bytes == 0) {
            log_debug("invalid input");
            return;
        }
    }
}


void SenMLCborParser::processDouble(double value){
    switch (this->curLabel)
    {
        //case SENML_CBOR_S_LABEL:
        case SENML_CBOR_BV_LABEL: this->baseValue.baseDouble = value; break;
        case SENML_CBOR_V_LABEL:
            double calculated = this->baseValue.baseDouble + value;
            this->setValue(&calculated, sizeof(double), CBOR_TYPE_DOUBLE); 
            break;
    }
}

unsigned int SenMLCborParser::parseNext()
{
    switch (CBOR_TYPE) {
        case CBOR_UINT:     return this->processUnsignedInt();
        case CBOR_NEGINT:   return this->processInt();
        case CBOR_BYTES:    return this->processBytes(CBOR_TYPE_DATA);
        case CBOR_TEXT:     return this->processBytes(CBOR_TYPE_STRING); 
        case CBOR_ARRAY:    return this->processArray();
        case CBOR_MAP:      return this->processMap();
        case CBOR_7: {
            bool boolRes;
            float floatVal;
            double doubleVal;
            size_t read_bytes;
            switch ((int)peekChar()) {
                case CBOR_FALSE:   
                    readChar();                                         //need to remove the char from the stream.
                    boolRes = false;
                    this->setValue((void*)&boolRes, sizeof(boolRes), CBOR_TYPE_BOOL); 
                    return 1;
                case CBOR_TRUE:     
                    readChar();                                         //need to remove the char from the stream.
                    boolRes = true;
                    this->setValue((void*)&boolRes, sizeof(boolRes), CBOR_TYPE_BOOL); 
                    return 1;
                case CBOR_FLOAT16:  
                    read_bytes = cbor_deserialize_float_half(&floatVal);
                    this->processDouble(floatVal); 
                    return read_bytes;
                case CBOR_FLOAT32:
                    read_bytes = cbor_deserialize_float(&floatVal);
                    this->processDouble(floatVal); 
                    return read_bytes;
                case CBOR_FLOAT64:
                    read_bytes = cbor_deserialize_double(&doubleVal);
                    this->processDouble(doubleVal); 
                    return read_bytes;
            }
        }
    }
    return 0;                                                                   //if we get here, something went wrong
}

void SenMLCborParser::setValue(void* value, int length, SenMLDataType type)
{
    if(this->curRec){
        this->curRec->actuate((const char*)value, length, type);
    }
    else {
        SenMLPack* pack = this->curPack;
        if(!pack)
            pack = this->root;
        if(pack)
            pack->actuate(this->curPackName.c_str(), this->curRecName.c_str(), value, length, type);
    }
}

void SenMLCborParser::setBinaryValue(const char* value, int length)
{
    if(this->curRec){
        ((SenMLBinaryActuator*)this->curRec)->actuate(value, length);
    }
    else {
        SenMLPack* pack = this->curPack;
        if(!pack)
            pack = this->root;
        if(pack)
            pack->actuate(this->curPackName.c_str(), this->curRecName.c_str(), value, length, CBOR_TYPE_DATA);
    }
}