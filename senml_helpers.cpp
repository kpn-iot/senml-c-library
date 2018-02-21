#include <senml_helpers.h>
#include <Base64.h>

#include <arduino.h>

void printDouble(double f, unsigned int digits, Stream* res) 
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
        res->print("INF");
        return;
    }
    // handle Not a Number
    if (isnan(f)) {
        res->print("NaN");
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
    res->print(s);
} // ===== end double2s()


void printBinaryAsBase64(const unsigned char* data, unsigned int length, Stream* res)
{
    int inputLen = sizeof(data);

    int encodedLen = base64_enc_len(inputLen);
    char encoded[encodedLen];
        
    // note input is consumed in this step: it will be empty afterwards
    base64_encode(encoded, (const char*)data, inputLen); 
    res->print(encoded);
}

void printUnit(SenMLUnit unit, Stream* res)
{
    if(unit != SENML_UNIT_NONE)
        res->print(senml_units_names[unit]);
}

