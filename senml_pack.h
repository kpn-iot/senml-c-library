#ifndef SENMLPACK
#define SENMLPACK

#include <senml_base.h>


#define PACK_ACTUATOR_SIGNATURE void (*callback)(const char*, const char*, const char*, SenMLDataType)

class SenMLPack: public SenMLBase
{
    friend class ActuatorListener; 
    public:
        SenMLPack(const char* baseName): SenMLPack(baseName, SENML_UNIT_NONE, NAN) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit): SenMLPack(baseName, baseUnit, NAN) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit, double baseTime): _bn(baseName), 
                                                                            _bu(baseUnit), 
                                                                            _bt(baseTime),
                                                                            _end(NULL) {};

        SenMLPack(PACK_ACTUATOR_SIGNATURE): SenMLPack("", SENML_UNIT_NONE, NAN, callback) {};
        SenMLPack(const char* baseName, PACK_ACTUATOR_SIGNATURE): SenMLPack(baseName, SENML_UNIT_NONE, NAN, callback) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit, PACK_ACTUATOR_SIGNATURE): SenMLPack(baseName, baseUnit, NAN, callback) {};
        SenMLPack(const char* baseName, SenMLUnit baseUnit, double baseTime, PACK_ACTUATOR_SIGNATURE): _bn(baseName), 
                                                                                                    _bu(baseUnit), 
                                                                                                    _bt(baseTime),
                                                                                                    _end(NULL),
                                                                                                    callback(callback)
                                                                                                    {};
        ~SenMLPack(){};

        //store the object that will contain all the log entries
        static void SetLogger(Stream *value) { _senml_logger = value; };

        //render the content of the current object to json data (string)
        void toJson(Stream *dest);

        //read a senml json string from the specified source and, for each registered actuator, call the
        //appropriate event.
        void fromJson(Stream *source);

        void fromJson(const char *source);

        void toCbor(Stream *dest);

        void setBaseName(const char* name);
        const char* getBaseName();
        void settBaseUnit(SenMLUnit unit);
        SenMLUnit getBaseUnit();
        /*set bt to NaN for not including it in the output*/
        void setBaseTime(double time);
        double getBaseTime();

        bool add(SenMLBase* item);
        bool clear();
        //get the first recrod of in this pack element.
        SenMLBase* getFirst() { return this->_start; }

        /*
        renders all the fields to json, without the starting and ending brackets.
        Inheriters can extend this function if they want to add extra fields to the json output
        */
        virtual void fieldsToJson(Stream *dest);

    protected:

        //derived classes can use this function to see if the root object (getRoot) is a SenMLPack
        //class or not.
        virtual bool isPack() override { return true; }

        virtual void actuate(const char* pack, const char* record, const char* value, SenMLDataType dataType);

        //store a ref to the last item in the list for quick link operations
        void setLast(SenMLBase* value);

        //renders the content of the pack object without []
        void contentToCbor(Stream *dest);    


        void fieldsToCbor(Stream *dest);

        //calculates the nr of items that there will be in the json array in senml representation
        //this is used for rendering cbor which needs to declare the nr of elements in an array.
        int getArrayLength() override;

    private:
        String _bn;
        SenMLUnit _bu;
        double _bt;
        SenMLBase *_end;                                //keeps track of the end of the list
        SenMLBase *_start;                              //keeps track of the start of the list
        PACK_ACTUATOR_SIGNATURE;                        //for registering actuator callbacks.
        
        
        //renders the content of the pack object without []
        void contentToJson(Stream *dest);              

        //calculates the nr of json fields that this object uses in a senml structure
        int getFieldLength() override;
};


#endif // SENMLPACK
