#ifndef SENMLBINARYACTUATOR
#define SENMLBINARYACTUATOR

#include <senml_binary_record.h>

#define BINARY_ACTUATOR_SIGNATURE void (*callback)(const unsigned char*, int)

class SenMLBinaryActuator: public SenMLBinaryRecord
{
public:
    SenMLBinaryActuator(const char* name, BINARY_ACTUATOR_SIGNATURE): SenMLBinaryActuator(name, SENML_UNIT_NONE, callback){};
    SenMLBinaryActuator(const char* name, SenMLUnit unit, BINARY_ACTUATOR_SIGNATURE): SenMLBinaryRecord(name, unit), callback(callback){};
    ~SenMLBinaryActuator(){};

protected:

    //called while parsing a senml message, when the parser found the value for an ActuatorListener
    void actuate(const char* value, SenMLDataType dataType) override;

private:
    BINARY_ACTUATOR_SIGNATURE;
};

#endif // SENMLBINARYACTUATOR