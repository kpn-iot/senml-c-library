#ifndef SENMLACTUATORLISTENER
#define SENMLACTUATORLISTENER

#include "JsonListener.h"
#include <senml_pack.h>
#include <senml_record.h>

class ActuatorListener: public JsonListener {

  public:
    ActuatorListener(SenMLPack* root): JsonListener(), root(root), curPack(root) {};


    virtual void key(String key);
    virtual void value(String value);

    //the following need to be implemented cause they are abstract in the base class.
    virtual void whitespace(char c){};
    virtual void startDocument(){};
    virtual void endArray(){};
    virtual void endObject(){};
    virtual void endDocument(){};
    virtual void startArray(){};
    virtual void startObject(){};



  private:
    int expected;               //name of key who's value is expected next
    SenMLPack* root;                    //the root document for which we are parsing. Used to search the up all the actuators.
    SenMLPack* curPack;                 //used while searching, to store the current pack to use. init to root pack by default
    SenMLRecord* curRec;
    String curRecName;                  //keeps a ref of the record name, for raising events for unknown records
    String curPackName;                 //name of hte current pack to send the actuator to.

    //looks up the pack object that has to contain the next field. This is in order
    //to support multiple packs (gateway functionality)
    void setCurrentPack(String& name);


    //check if base units mathc, if not, show error message
    void checkBaseUnit(String& name);

    //look up a record with the spedified name in the current pack 
    void setCurrentRecord(String& name);

    void setValue(String& value, SenMLDataType dataType);
};

#endif // SENMLACTUATORLISTENER