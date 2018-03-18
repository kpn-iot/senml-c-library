#ifndef SENMLHELPERS
#define SENMLHELPERS

#ifdef __MBED__
    #include "mbed.h"
    #include "sstream"
#else
    #include <stream.h>
#endif
#include <senml_enums.h>
#include <math.h> 


typedef struct StreamContext_t{
    Stream* stream;
    SenMLStreamMethod format;
} StreamContext;

extern StreamContext* _streamCtx;

//write a double as string to the stream.
void printDouble(double f, unsigned int digits) ;

//convert the data array to base64 string and write to stream
void printBinaryAsBase64(const unsigned char* data, unsigned int length);

//convert the unit to string and write to stream.
void printUnit(SenMLUnit unit);

void printText(const char*value, int len);



//read a character from the current data stream (_streamCtx) 
//takes into account that the stream might contain hex values.
char readChar();

//peek a character from the current data stream.
//takes into account that the stream might contain hex values.
char peekChar();

inline void readChars(unsigned char* buffer, int len)
{
    for(int i = 0; i < len; i++){
        buffer[i] = readChar();
    }
}

#endif // SENMLHELPERS