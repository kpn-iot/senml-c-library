#ifndef SENMLBASE
#define SENMLBASE

#include <stream.h>
#include <senml_enums.h>
#include <math.h>

//contains a referenc to the global logger object assigned to the module
extern Stream* _senml_logger;
void senMLSetLogger(Stream* logger);

#ifndef log_debug
#define log_debug(...)  if(_senml_logger) _senml_logger->println(__VA_ARGS__)
#endif


class SenMLBase
{
friend class SenMLPack; 
friend class SenMLRecord; 
friend class ActuatorListener; 
public:
    SenMLBase();
    ~SenMLBase();

    //render the content of the senml object to the specified stream. This will produce a json string
    virtual void toJson(Stream *dest) {};

    //render the content of the senml object to the specified stream. This will produce a binary data blob
    virtual void toCbor(Stream *dest) {};

    //get the next item in the list
    SenMLBase* getNext(){ return this->_next; };

    //get the root object of this list. Usually, this is a SenMLPack object.
    SenMLBase* getRoot();

    //This function is called by the root SenMLPack object to indicate that the object
    //should adjust it's time info relative to the new base time (if applicable)
    //doesn't do anything by default
    //params: prev: previous base time
    //        time: new base time
    virtual void adjustToBaseTime(double prev, double time) {};

    /*
    renders all the fields to json, without the starting and ending brackets.
    Inheriters can extend this function if they want to add extra fields to the json output
    note: tihs is public so that custom implementations for the record object can use other objects internally and render to json using this function (ex: coordinatesRecord using 3 floatRecrods for lat, lon & alt.
    */
    virtual void fieldsToJson(Stream *dest) = 0;

protected:
    //assign the element in the list that this object points to.
    virtual void setNext(SenMLBase* value);
    //SenMLPack overrides this function cause it keeps track of the last item in the list
    virtual void setLast(SenMLBase* value){};
    //assign the previous element in the list that thisobject points to.
    void setPrev(SenMLBase* value);
    //assign the previous element in the list that thisobject points to.
    SenMLBase* getPrev();

    //derived classes can use this function to see if the root object (getRoot) is a SenMLPack
    //class or not.
    virtual bool isPack() { return false; }

    //renders the content of the pack object without [], but still with {} for objects
    virtual void contentToCbor(Stream *dest){};    

    //renders all the fields to cbor format. renders all the fields of the object without the {}
    virtual void fieldsToCbor(Stream *dest){};

    //calculates the nr of items that this object will put in the json array in senml representation
    //this is used for rendering cbor which needs to declare the nr of elements in an array.
    //packs can have multiple elements in the array, but also custom implementations for records that wrap muliple 
    //records.
    virtual int getArrayLength() { return 1; };

    //calculates the nr of fields that this object will produce.
    virtual int getFieldLength() {};


private:
    SenMLBase* _next;                               //reference to the next element in the list.
    SenMLBase* _prev;                               //reference to the previous element, needed for deletion of record
};



#endif // SENMLBASE