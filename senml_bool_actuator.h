#ifndef SENMLBOOLACTUATOR
#define SENMLBOOLACTUATOR

#include <senml_bool_record.h>

#define BOOL_ACTUATOR_SIGNATURE void (*callback)(bool)

class SenMLBoolActuator: public SenMLBoolRecord
{
public:
    SenMLBoolActuator(const char* name, BOOL_ACTUATOR_SIGNATURE): SenMLBoolRecord(name, SENML_UNIT_NONE, false), callback(callback) {};
    SenMLBoolActuator(const char* name, SenMLUnit unit, BOOL_ACTUATOR_SIGNATURE): SenMLBoolRecord(name, unit, false), callback(callback) {};
    SenMLBoolActuator(const char* name, SenMLUnit unit, bool value, BOOL_ACTUATOR_SIGNATURE):  SenMLBoolRecord(name, unit, value), callback(callback) {};
    ~SenMLBoolActuator(){};

protected:

    //called while parsing a senml message, when the parser found the value for an SenMLJsonListener
    virtual void actuate(const void* value, int dataLength, SenMLDataType dataType);

private:
    BOOL_ACTUATOR_SIGNATURE;
};

#endif // SENMLBOOLACTUATOR






