#ifndef SENMLBINARYRECORD
#define SENMLBINARYRECORD

#include <senml_record.h>

class SenMLBinaryRecord: public SenMLRecord
{
public:
    SenMLBinaryRecord(const char* name);
    SenMLBinaryRecord(const char* name, SenMLUnit unit);
    ~SenMLBinaryRecord(){ if(this->_value) free(this->_value); };


    /*set the value and length.
    warning: value is not copied over. a direct reference to the buffer is stored, so if this
    memory is changed/freed, then the data stored in the object will also be changed.
    */
    bool set(unsigned char* value, unsigned int length, double time = NAN);

    /*
    renders all the fields to json, without the starting and ending brackets.
    Inheriters can extend this function if they want to add extra fields to the json output
    Note: binary data is rendered as base64url-encoded
    */
    void fieldsToJson();

protected:

    //renders all the fields to cbor format. renders all the fields of the object without the {}
    virtual int fieldsToCbor();
    
private:
    unsigned char* _value;                  //raw data buffer (not null terminated)
    unsigned int _length;                   //size of the _data packet

};

#endif // SENMLBINARYRECORD






