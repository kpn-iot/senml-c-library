#ifndef SENMLFLOATACTUATOR
#define SENMLFLOATACTUATOR

#include <senml_float_record.h>

#define FLOAT_ACTUATOR_SIGNATURE void (*callback)(float)

class SenMLFloatActuator: public SenMLFloatRecord
{
public:
    SenMLFloatActuator(const char* name, FLOAT_ACTUATOR_SIGNATURE): SenMLFloatActuator(name, SENML_UNIT_NONE, 0.0, callback){};
    SenMLFloatActuator(const char* name, SenMLUnit unit, FLOAT_ACTUATOR_SIGNATURE): SenMLFloatActuator(name, unit, 0.0, callback){};
    SenMLFloatActuator(const char* name, SenMLUnit unit, float value, FLOAT_ACTUATOR_SIGNATURE):  SenMLFloatRecord(name, unit, value), callback(callback) {};
    ~SenMLFloatActuator(){};

protected:

    //called while parsing a senml message, when the parser found the value for an ActuatorListener
    void actuate(const char* value, SenMLDataType dataType) override;

private:
    FLOAT_ACTUATOR_SIGNATURE;
};

#endif // SENMLFLOATACTUATOR