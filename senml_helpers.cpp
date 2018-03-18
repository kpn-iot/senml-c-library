#include <senml_helpers.h>

#ifdef ESP32
    #include <base64.h>
#elif __MBED__
    #include <base64.h>
    int base64_enc_len(int plainLen) {
	    int n = plainLen;
	    return (n + 2 - ((n + 2) % 3)) / 3 * 4;
    }
#else
    #include <Base64.h>
#endif

//#include <arduino.h>


//global reference to the stream and stream configuration. This should save us memory
//by not having to pass these values continuously on the stack.
StreamContext* _streamCtx = NULL;

void printDouble(double f, unsigned int digits) 
{
    int d;
    static char s[26]; // formated number as string
    int index = 0;

    // handle sign
    if (f < 0.0) {
        s[index++] = '-';
        f = -f;
    }
    // handle infinite values
    if (isinf(f)) {
        printText("INF", 3);
        return;
    }
    // handle Not a Number
    if (isnan(f)) {
        printText("NaN", 3);
        return;
    }

    // max digits
    if (digits > 16) digits = 16;
    int exponent = int(log10(f));
    double g = f / pow(10, exponent);
    if ((g < 1.0) && (g != 0.0)) {
        g *= 10;
        exponent--;
    }
    if (exponent < -330) { // lower limit of double-precision on Teensy 3
        g = 0;
        exponent = 0;
    }
    if (digits < 16) { // display number rounded at last digit
        g += 0.5 / pow(10, digits);
    }

    d = g;
    sprintf( & s[index++], "%d", d);
    if(exponent < 4){
        for(int i = 1; i <= exponent && i < 4; i++){    
            g = (g - d) * 10.0; // shift one decimal place to the left
            d = int(g);
            sprintf( & s[index++], "%d", d);
        }
        exponent -= (exponent > 4 ? 4 : exponent );
    }
    if (digits > 0) sprintf( & s[index++], ".");
    for (int i = 0; i < digits; i++) {
        g = (g - d) * 10.0; // shift one decimal place to the left
        d = int(g);
        sprintf( & s[index++], "%d", d);
    }
    for(int i = digits -1; i >0; i--){                              //remove unwanted trailing 0
        if(s[i] != '0'){
            if(s[i] == '.')                                         //if we end on something like x.  then add a last 0, so that it becomes x.0
                s[i+ 1] = '0';
            break;
        }
        s[i] = 0;                                                   //set new end of string.
    }
    if(exponent != 0)                                               //only print the exponent if it has a meaning.
        sprintf( & s[index], "E%+d", exponent);
    printText(s, strlen(s));
} // ===== end double2s()


void printBinaryAsBase64(const unsigned char* data, unsigned int length)
{
    int inputLen = sizeof(data);

    #ifdef ESP32
        String encoded = base64::encode((uint8_t*)data, inputLen);
        printText(encoded.c_str(), encoded.length());
    #else
        int encodedLen = base64_enc_len(inputLen);
        char encoded[encodedLen];
        
        #ifdef __MBED__
            // todo: check result of function
            size_t olen;
            mbedtls_base64_encode((unsigned char*)encoded, encodedLen, &olen, data, length);
        #else
            // note input is consumed in this step: it will be empty afterwards
            base64_encode(encoded, (char*)data, inputLen); 
        #endif
        printText(encoded, encodedLen);
    #endif
}

void printUnit(SenMLUnit unit)
{
    if(unit != SENML_UNIT_NONE)
        printText(senml_units_names[unit], strlen(senml_units_names[unit]));
}

void printText(const char* value, int len)
{
    char hexTable[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    if(_streamCtx->format == SENML_RAW){
        #ifdef __MBED__
            for(int i = 0; i < len; i++)
                _streamCtx->stream->putc(value[i]);
        #else
            _streamCtx->stream->write(value, len);
        #endif
    }
    else if (_streamCtx->format == SENML_HEX){
        for(int i = 0; i< len; i++){
            #ifdef __MBED__
                _streamCtx->stream->putc(hexTable[value[i] /16]);
                _streamCtx->stream->putc(hexTable[value[i] % 16]);
            #else
                _streamCtx->stream->print(hexTable[value[i] /16]);
                _streamCtx->stream->print(hexTable[value[i] % 16]);
            #endif
        }
    }
}


static bool peeked = false;                     //if we peek the stream in HEX format, we actually need to read 2 bytes, so the peek doesn't work, but we need to read the actual value.
static char peekVal = 0;                        //these values are removed by the compiler if no cbor is used.

char readChar(){
    if(_streamCtx->format == SENML_RAW){
        #ifdef __MBED__
            return _streamCtx->stream->getc();
        #else
            return _streamCtx->stream->read();
        #endif
    }
    else if (_streamCtx->format == SENML_HEX){
        if(peeked == true){
            peeked = false;
            return peekVal;
        }
        #ifdef __MBED__
            int A = _streamCtx->stream->getc();
            int B = _streamCtx->stream->getc();
        #else
            int A = _streamCtx->stream->read();
            int B = _streamCtx->stream->read();
        #endif
        A = (A > '9')? (A &~ 0x20) - 'A' + 10: (A - '0');
        B = (B > '9')? (B &~ 0x20) - 'A' + 10: (B - '0');
        return (A * 16) + B;
    }
    else {                                                          //unsupported type
        return -1;
    }
};


char peekChar(){
    if(_streamCtx->format == SENML_RAW){
        #ifdef __MBED__
            peekVal = _streamCtx->stream->getc();
            peeked = true;
            return peekVal;
        #else
            return _streamCtx->stream->peek();
        #endif
    }
    else if (_streamCtx->format == SENML_HEX){
        #ifdef __MBED__
            int A = _streamCtx->stream->getc();
            int B = _streamCtx->stream->getc();
        #else
            int A = _streamCtx->stream->read();
            int B = _streamCtx->stream->read();
        #endif
        A = (A > '9')? (A &~ 0x20) - 'A' + 10: (A - '0');
        B = (B > '9')? (B &~ 0x20) - 'A' + 10: (B - '0');
        peekVal = (A * 16) + B;
        peeked = true;
        return peekVal;
    }
    else {                                                          //unsupported type
        return -1;
    }
};

