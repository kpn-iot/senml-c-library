#ifndef SENMLPACK
#define SENMLPACK

#ifdef __MBED__
    #include "mbed.h"
    #include <string> 
    using namespace std;
    #define String string
#endif

#include <senml_base.h>


#define PACK_ACTUATOR_SIGNATURE void (*callback)(const char*, const char*, const void*, int, SenMLDataType)

class SenMLPack: public SenMLBase
{
    friend class SenMLJsonListener; 
    friend class SenMLCborParser;
    friend class SenMLBase;
    public:
        SenMLPack(const char* baseName):  _bn(baseName),                                                    //mbed compiler doesnt support delegating constructors
                                          _bu(SENML_UNIT_NONE), 
                                          _bt(NAN),
                                          _end(NULL) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit):  _bn(baseName),                               
                                                              _bu(baseUnit), 
                                                              _bt(NAN),
                                                              _end(NULL) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit, double baseTime): _bn(baseName),                
                                                                              _bu(baseUnit), 
                                                                              _bt(baseTime),
                                                                              _end(NULL) {};

        SenMLPack(PACK_ACTUATOR_SIGNATURE): _bn(""),                                  
                                            _bu(SENML_UNIT_NONE), 
                                            _bt(NAN),
                                            _end(NULL),
                                            callback(callback) {};
        SenMLPack(const char* baseName, PACK_ACTUATOR_SIGNATURE): _bn(baseName), 
                                                                  _bu(SENML_UNIT_NONE), 
                                                                  _bt(NAN),
                                                                  _end(NULL),
                                                                  callback(callback) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit, PACK_ACTUATOR_SIGNATURE): _bn(baseName), 
                                                                                      _bu(baseUnit), 
                                                                                      _bt(NAN),
                                                                                      _end(NULL),
                                                                                      callback(callback) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit, double baseTime, PACK_ACTUATOR_SIGNATURE): _bn(baseName), 
                                                                                                       _bu(baseUnit), 
                                                                                                       _bt(baseTime),
                                                                                                       _end(NULL),
                                                                                                       callback(callback) {};
        ~SenMLPack(){};

        //render the content of the current object to json data (string)
        void toJson(Stream* dest, SenMLStreamMethod format=SENML_RAW);

        void toJson(char *dest, int length, SenMLStreamMethod format=SENML_RAW);

        //read a senml json string from the specified source and, for each registered actuator, call the
        //appropriate event.
        void fromJson(Stream* source, SenMLStreamMethod format=SENML_RAW);

        //parse json data into senml objects aand, for each registered actuator, call the
        //appropriate event. 
        //Takes a string as input
        void fromJson(const char* source);

        void fromCbor(Stream* source, SenMLStreamMethod format=SENML_RAW);
        
        void fromCbor(char* source, int length, SenMLStreamMethod format);

        void toCbor(Stream* dest, SenMLStreamMethod format=SENML_RAW);

        void toCbor(char *dest, int length, SenMLStreamMethod format=SENML_RAW);

        void setBaseName(const char* name);
        const char* getBaseName();
        void setBaseUnit(SenMLUnit unit);
        inline SenMLUnit getBaseUnit() { return this->_bu; };
        /*set bt to NaN for not including it in the output*/
        void setBaseTime(double time);
        inline double getBaseTime() { return this->_bt; };

        bool add(SenMLBase* item);
        bool clear();
        //get the first recrod of in this pack element.
        inline SenMLBase* getFirst() { return this->_start; };


    protected:

        /*
        renders all the fields to json, without the starting and ending brackets.
        Inheriters can extend this function if they want to add extra fields to the json output
        */
        virtual void fieldsToJson();

        virtual void fieldsToCbor();

        //derived classes can use this function to see if the root object (getRoot) is a SenMLPack
        //class or not.
        virtual bool isPack() { return true; }

        //when the user did not register a specific record actuator, this will be called.
        inline void actuate(const char* pack, const char* record, const void* value, int valueLength, SenMLDataType dataType)
        {
            if(this->callback)
                this->callback(pack, record, value, valueLength, dataType);
        };

        //store a ref to the last item in the list for quick link operations
        void setLast(SenMLBase* value);

        //renders the content of the pack object without []
        virtual void contentToCbor();    


        //calculates the nr of items that there will be in the json array in senml representation
        //this is used for rendering cbor which needs to declare the nr of elements in an array.
        virtual int getArrayLength();

        virtual void setupStreamCtx(char *dest, int length, SenMLStreamMethod format);

        virtual void setupStreamCtx(Stream *dest, SenMLStreamMethod format);

    private:
        String _bn;
        SenMLUnit _bu;
        double _bt;
        SenMLBase *_end;                                //keeps track of the end of the list
        SenMLBase *_start;                              //keeps track of the start of the list
        PACK_ACTUATOR_SIGNATURE;                        //for registering actuator callbacks.
        
        
        //renders the content of the pack object without []
        virtual void contentToJson();              

        //calculates the nr of json fields that this object uses in a senml structure
        virtual int getFieldLength();


        void internalToJson();

        inline char readHexChar(Stream *source){
            #ifdef __MBED__
                unsigned char first = source->getc();
                unsigned char second = source->getc();
            #else
                unsigned char first = source->read();
                unsigned char second = source->read();
            #endif
            first = (first < '9') ? first - '0' : first - '7';
            second = (second < '9') ? second - '0' : second - '7';
            return (16 * first) + second;
        };
};


#endif // SENMLPACK







