#ifndef SENMLPACKTEMPLATE
#define SENMLPACKTEMPLATE

#include <senml_pack.h>

template <class T>
class SenMLPackTemplate: public SenMLPack
{
    public:

        SenMLPackTemplate(const char* baseName): SenMLPack(baseName, SENML_UNIT_NONE, NAN) {};
        SenMLPackTemplate(const char* baseName, SenMLUnit baseUnit): SenMLPack(baseName, baseUnit, NAN) {};
        SenMLPackTemplate(const char* baseName, SenMLUnit baseUnit, double baseTime): SenMLPack(baseName, baseUnit, baseTime) {};

        SenMLPackTemplate(PACK_ACTUATOR_SIGNATURE): SenMLPack("", SENML_UNIT_NONE, NAN, callback) {};
        SenMLPackTemplate(const char* baseName, PACK_ACTUATOR_SIGNATURE): SenMLPack(baseName, SENML_UNIT_NONE, NAN, callback) {};
        SenMLPackTemplate(const char* baseName, SenMLUnit baseUnit, PACK_ACTUATOR_SIGNATURE): SenMLPack(baseName, baseUnit, NAN, callback) {};
        SenMLPackTemplate(const char* baseName, SenMLUnit baseUnit, double baseTime, PACK_ACTUATOR_SIGNATURE): SenMLPack(baseName, baseUnit, baseTime, callback){};



        ~SenMLPackTemplate(){};

        T getBaseSum() {return _sum; } ;
        bool setBaseSum(T value) {_sum = value; return true;};

        T getBaseValue() {return _value; } ;
        bool setBaseValue(T value) {_value = value; return true;};

protected:


private:
    T _sum;
    T _value;
};

#endif // SENMLPACKTEMPLATE