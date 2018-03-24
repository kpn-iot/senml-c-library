#include <senml_helpers.h>

#ifdef ESP32
    #include <base64.h>
    #include <arduino.h>                        //needed for sprintf
#elif __MBED__
    #include <base64.h>
    int base64_enc_len(int plainLen) {
	    int n = plainLen;
	    return (n + 2 - ((n + 2) % 3)) / 3 * 4;
    }
#else
    #include <Base64.h>
#endif



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
    //if (digits < 16) { // display number rounded at last digit
    //    g += 0.5 / pow(10, digits);
    //}

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
    for(int i = index -1; i >0; i--){                              //remove unwanted trailing 0
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

    if(_streamCtx->dataAsBlob){
        if(_streamCtx->format == SENML_RAW){
            for(int i = 0; i < len; i++){
                if(_streamCtx->data.blob.curPos >= _streamCtx->data.blob.length) return;            //if we reached the end of the buffer, stop rendering otherwise we overwrite some other mem which is not good.
                _streamCtx->data.blob.data[_streamCtx->data.blob.curPos++] = value[i];
            }
        }
        else{
            for(int i = 0; i < len; i++){
                if(_streamCtx->data.blob.curPos >= _streamCtx->data.blob.length) return;            //if we reached the end of the buffer, stop rendering otherwise we overwrite some other mem which is not good.
                _streamCtx->data.blob.data[_streamCtx->data.blob.curPos++] = hexTable[value[i] / 16];
                _streamCtx->data.blob.data[_streamCtx->data.blob.curPos++] = hexTable[value[i] % 16];
            }
        }
    }
    else{
        if(_streamCtx->format == SENML_RAW){
            #ifdef __MBED__
                for(int i = 0; i < len; i++)
                    _streamCtx->data.stream->putc(value[i]);
            #else
                _streamCtx->data.stream->write(value, len);
            #endif
        }
        else if (_streamCtx->format == SENML_HEX){
            for(int i = 0; i< len; i++){
                #ifdef __MBED__
                    _streamCtx->data.stream->putc(hexTable[value[i] / 16]);
                    _streamCtx->data.stream->putc(hexTable[value[i] % 16]);
                #else
                    _streamCtx->data.stream->print(hexTable[value[i] / 16]);
                    _streamCtx->data.stream->print(hexTable[value[i] % 16]);
                #endif
            }
        }
    }
}

static bool peeked = false;                     //if we peek the stream in HEX format, we actually need to read 2 bytes, so the peek doesn't work, but we need to read the actual value.
static int peekVal = 0;                        //these values are removed by the compiler if no cbor is used.

int readChar(){
    if(peeked == true){
        peeked = false;
        return peekVal;
    }
    int res;
    if(_streamCtx->dataAsBlob){
		if(_streamCtx->data.blob.curPos < _streamCtx->data.blob.length)         //peekchar has to return -1 if there is no more data, so check for this.
			res = _streamCtx->data.blob.data[_streamCtx->data.blob.curPos++];
		else
			return -1;
        if(_streamCtx->format == SENML_HEX){
            int resB = _streamCtx->data.blob.data[_streamCtx->data.blob.curPos++];
            res = (res > '9')? (res &~ 0x20) - 'A' + 10: (res - '0');
	        resB = (resB > '9')? (resB &~ 0x20) - 'A' + 10: (resB - '0');
            res = (res * 16) + resB;
        }
	} 
	else {                                                                      //data is comming from the stream, this already returns -1 if there is no data.
        if(_streamCtx->format == SENML_RAW){
            #ifdef __MBED__
                res = _streamCtx->data.stream->getc();
            #else
                res = _streamCtx->data.stream->available() ? _streamCtx->data.stream->read() : -1;                          //arduino stream, check if something is available, if not, we can't read anymore.
            #endif
        }
        else{
            int resB;
            #ifdef __MBED__
                res = _streamCtx->data.stream->getc();
                resB = _streamCtx->data.stream->getc();
            #else
              
                if(_streamCtx->data.stream->available())
                    res = _streamCtx->data.stream->read();
                else
                    return -1;
                if(_streamCtx->data.stream->available())
                    resB = _streamCtx->data.stream->read();
                else
                    return -1;
            #endif
            res = (res > '9')? (res &~ 0x20) - 'A' + 10: (res - '0');
            resB = (resB > '9')? (resB &~ 0x20) - 'A' + 10: (resB - '0');
            res = (res * 16) + resB;
        }
	}
    return res;
};

int peekChar(){
    if(peeked == true)                                                              //if already peeked, return the currently buffered value.
        return peekVal;
    peekVal = readChar();
    if(peekVal != -1)                                                               //if no more data, don't try to buffer it, some new data might arrive later on
        peeked = true;
    return peekVal;
};

void flush(){
    peeked = false;
}


