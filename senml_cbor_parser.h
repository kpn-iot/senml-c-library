#ifndef SENMLCBORPARSER
#define SENMLCBORPARSER

#include <senml_base_parser.h>
#include <senml_enums.h>
#include <senml_logging.h>
#include <senml_helpers.h>
#include <cbor.h>

enum SenMLCborDataType {};

#define SENML_CBOR_KEY 1
#define SENML_CBOR_VALUE 2


class SenMLCborParser: public SenMLBaseParser {

  public:
    SenMLCborParser(SenMLPack* root, SenMLStreamMethod format): SenMLBaseParser(root), state(0) 
    {
        this->ctx.format = format;
        this->ctx.baseValue.baseUint = 0;               //init to 0, so we get correct results for first element as well.
        this->ctx.baseSum.baseUint = 0;
        _streamCtx = &this->ctx;                                     //set the global variable so that we don't have to pass it along on the stack all the time (saves mem & codesize)
    };

    //convert the cbor raw data into senml and actuate the records in the root pack.
    void parse(Stream* source);


    void parse(char* source, int length);


  private:
    unsigned char state;                                            //keeps track of the current parse state
    int curLabel;                                         //the cbor number that represents the current senml label (unit, value, boolvalue, basename,..). The next item to read has to be the value for the label
    StreamContext ctx;

    unsigned int parseNext();

    void setValue(void* value, int length, SenMLDataType type);
    void setBinaryValue(const char* value, int length);
    void processDouble(double value);

    void internalParse();

    unsigned int processArray()
    {
        const bool is_indefinite = (peekChar() == (CBOR_ARRAY | CBOR_VAR_FOLLOWS));
        uint64_t array_length = 0;
        size_t read_bytes;

        if (is_indefinite){
            log_debug("not supported");
        }
        else
            read_bytes = decode_int(&array_length);

        size_t i = 0;

        while (i < array_length) {
            size_t inner_read_bytes = this->parseNext();
            if (inner_read_bytes == 0) {
                log_debug("invalid input");
                break;
            }
            read_bytes += inner_read_bytes;
            ++i;
        }

        return read_bytes;
    };

    inline unsigned int processMap()
    {
        const bool is_indefinite = (peekChar() == (CBOR_MAP | CBOR_VAR_FOLLOWS));
        uint64_t map_length = 0;
        size_t read_bytes;

        if (is_indefinite){
            log_debug("not supported");
        }
        else 
            read_bytes = decode_int(&map_length);

        unsigned char curState = this->state;
        size_t i = 0;
        while (i < map_length) {
            size_t key_read_bytes, value_read_bytes;
            this->state = SENML_CBOR_KEY;
            key_read_bytes = this->parseNext(); /* key */
            this->state = SENML_CBOR_VALUE;
            value_read_bytes = this->parseNext(); /* value */
            if (key_read_bytes == 0 || value_read_bytes == 0) {
                log_debug("invalid input");
                break;
            }
            read_bytes += key_read_bytes + value_read_bytes;
            ++i;
        }
        this->state = curState;                                     //reset to the original state. was changed inside loop
        this->ctx.baseValue.baseUint = 0;                                        //if there was a base value, reset it for the next run.
        return read_bytes;
    };

    inline unsigned int processUnsignedInt()
    {
        uint64_t val; 
        size_t read_bytes = cbor_deserialize_uint64_t(&val); 
        if(this->state == SENML_CBOR_VALUE){
            switch (this->curLabel)
            {
                case SENML_CBOR_BV_LABEL: this->ctx.baseValue.baseUint = val; break;
                case SENML_CBOR_V_LABEL: 
                    uint64_t calculated = this->ctx.baseValue.baseUint + val;
                    this->setValue((void*)&calculated, sizeof(uint64_t), CBOR_TYPE_UINT); 
                    break;
            }
        }
        else if(this->state == SENML_CBOR_KEY)             //store the value type (basename, baseunit, value, stringvalue,...)
            this->curLabel = (int)val;
        return read_bytes; 
    };

    inline unsigned int processInt()
    {
        int64_t val; 
        size_t read_bytes = cbor_deserialize_int64_t(&val); 
        if(this->state == SENML_CBOR_VALUE){
            switch (this->curLabel)
            {
                case SENML_CBOR_BV_LABEL: this->ctx.baseValue.baseInt = val; break;
                case SENML_CBOR_V_LABEL: 
                uint64_t calculated = this->ctx.baseValue.baseInt + val;
                    this->setValue((void*)&calculated, sizeof(int64_t), CBOR_TYPE_INT); 
                    break;
            }
        }
        else if(this->state == SENML_CBOR_KEY)             //store the value type (basename, baseunit, value, stringvalue,...)
            this->curLabel = val;
        return read_bytes; 
    };

    inline unsigned int processBytes(SenMLDataType type)
    {
        uint64_t bytes_length;                              //needs to be this big for decode_int
        size_t bytes_read = decode_int(&bytes_length);
        
        if(bytes_read == 0) return 0;
        char buffer[bytes_length + 1];                      //need a null 
        for(int i = 0; i < (int)bytes_length; i++)
            buffer[i] = readChar();
        buffer[bytes_length] = 0;                           //close it, just to be save. not always needed, but it is for strings

        if(type == CBOR_TYPE_DATA){                         //we are expecting binary data, so it has to be for a binary data value.
            if(this->curLabel == SENML_CBOR_VD_LABEL)
                this->setBinaryValue(buffer, bytes_length); 
            else
                log_debug("invalid input");
        }else{                                              //its text
            String value;
            switch (this->curLabel)
            {
                case SENML_CBOR_BN_LABEL: 
                    value = buffer;
                    this->setCurrentPack(value); 
                    break;
                case SENML_CBOR_BU_LABEL: 
                    value = buffer;
                    this->checkBaseUnit(value); 
                    break;
                case SENML_CBOR_N_LABEL:
                    value = buffer;
                    this->setCurrentRecord(value); 
                    break;
                case SENML_CBOR_VS_LABEL:
                    this->setValue((void*)buffer, bytes_length, CBOR_TYPE_STRING);
                     break;
            }
        }
        return bytes_read + bytes_length;
    };
};

#endif // SENMLCBORPARSER






