#ifndef SENMLINTACTUATOR
#define SENMLINTACTUATOR

#include <senml_int_record.h>

#define INT_ACTUATOR_SIGNATURE void (*callback)(int)

class SenMLIntActuator: public SenMLIntRecord
{
public:
    SenMLIntActuator(const char* name, INT_ACTUATOR_SIGNATURE): SenMLIntActuator(name, SENML_UNIT_NONE, 0, callback){};
    SenMLIntActuator(const char* name, SenMLUnit unit, INT_ACTUATOR_SIGNATURE): SenMLIntActuator(name, unit, 0, callback){};
    SenMLIntActuator(const char* name, SenMLUnit unit, int value, INT_ACTUATOR_SIGNATURE):  SenMLIntRecord(name, unit, value), callback(callback) {};
    ~SenMLIntActuator(){};

protected:

    //called while parsing a senml message, when the parser found the value for an ActuatorListener
    void actuate(const char* value, SenMLDataType dataType) override;

private:
    INT_ACTUATOR_SIGNATURE;
};

#endif // SENMLINTACTUATOR