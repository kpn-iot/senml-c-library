#ifndef SENMLPACKTEMPLATE
#define SENMLPACKTEMPLATE

#include <senml_pack.h>

template <class T>
class SenMLPackTemplate: public SenMLPack
{
public:
    SenMLPackTemplate(const char* name);
    ~SenMLPackTemplate(){};

    T getBaseSum() {return _sum; } ;
    virtual bool setBaseSum(T value) {_sum = value;};

    T getBaseValue() {return _value; } ;
    virtual bool setBaseValue(T value) {_value = value;};

protected:


private:
    T _sum;
    T _value;
};

#endif // SENMLPACKTEMPLATE