#ifndef SENMLHELPERS
#define SENMLHELPERS

#include <stream.h>
#include <senml_enums.h>
#include <math.h> 


//write a double as string to the stream.
void printDouble(double f, unsigned int digits, Stream* res) ;

//convert the data array to base64 string and write to stream
void printBinaryAsBase64(const unsigned char* data, unsigned int length, Stream* res);

//convert the unit to string and write to stream.
void printUnit(SenMLUnit unit, Stream* res);


#endif // SENMLHELPERS