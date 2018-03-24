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

#ifndef SENML_MAX_DOUBLE_PRECISION
#define SENML_MAX_DOUBLE_PRECISION 4
#endif // !SENML_MAX_DOUBLE_PRECISION

//store the base value to be used
typedef union BaseData_t{
    uint64_t baseUint;
    int64_t baseInt;
    double baseDouble;
} BaseData;

typedef struct SenmlMemoryData_t{
    char* data;                             //pointer to the buffer that constitutes the input/output buffer
    int curPos;                             //current position in the buffer.
    int length;                             //length of the memory buffer.
} SenmlMemoryData;                          //a record used when the input for the parser or output for the renderer is a data blob stored in memory

typedef union SenmlData_t{
    Stream* stream;
    SenmlMemoryData blob;
} SenmlData;                                //choose between input/outpu from a stream object (ex: direct input from uart) or from buffered data.

typedef struct StreamContext_t{
    bool dataAsBlob;                        //when true, data is from a memory blob, otherwise it comes from/goes to a stream object (ex: direct from/to uart)
    SenmlData data;                         //the data source to be parsed or destination to render to. can be from a stream or from data buffered in memory
    SenMLStreamMethod format;
    BaseData baseValue;                     //filled in when records need to adjust while rendering data.
    BaseData baseSum;
    SenMLDataType baseDataType;             //so we know which data type to use for baseValue and baseSum
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
int readChar();

//peek a character from the current data stream.
//takes into account that the stream might contain hex values.
int peekChar();

//flush and reset all input for the current data stream.
void flush();

inline void readChars(unsigned char* buffer, int len)
{
    for(int i = 0; i < len; i++){
        buffer[i] = readChar();
    }
}

inline bool charAvailable(){
    if(_streamCtx->dataAsBlob){
        return _streamCtx->data.blob.curPos < _streamCtx->data.blob.length;
    }
    else{
        #ifdef __MBED__
            return _streamCtx->data.stream->readable() != 0;      
        #else  
            return _streamCtx->data.stream->available() != 0; 
        #endif
    }
}

#endif // SENMLHELPERS






