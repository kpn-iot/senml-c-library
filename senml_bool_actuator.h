#ifndef SENMLBOOLACTUATOR
#define SENMLBOOLACTUATOR

#include <senml_bool_record.h>

#define BOOL_ACTUATOR_SIGNATURE void (*callback)(bool)

class SenMLBoolActuator: public SenMLBoolRecord
{
public:
    SenMLBoolActuator(const char* name, BOOL_ACTUATOR_SIGNATURE): SenMLBoolActuator(name, SENML_UNIT_NONE, false, callback){};
    SenMLBoolActuator(const char* name, SenMLUnit unit, BOOL_ACTUATOR_SIGNATURE): SenMLBoolActuator(name, unit, false, callback){};
    SenMLBoolActuator(const char* name, SenMLUnit unit, bool value, BOOL_ACTUATOR_SIGNATURE):  SenMLBoolRecord(name, unit, value), callback(callback) {};
    ~SenMLBoolActuator(){};

protected:

    //called while parsing a senml message, when the parser found the value for an ActuatorListener
    void actuate(const char* value, SenMLDataType dataType) override;

private:
    BOOL_ACTUATOR_SIGNATURE;
};

#endif // SENMLBOOLACTUATOR