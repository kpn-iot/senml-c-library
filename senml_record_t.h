#ifndef SENMLRECORDTEMPLATE
#define SENMLRECORDTEMPLATE

#include <senml_record.h>



template <class T>
class SenMLRecordTemplate: public SenMLRecord
{
public:
    SenMLRecordTemplate(const char* name): SenMLRecord(name), _valAsSum(false){};
    SenMLRecordTemplate(const char* name, SenMLUnit unit):  SenMLRecord(name, unit), _valAsSum(false){};
    SenMLRecordTemplate(const char* name, SenMLUnit unit, T value):  SenMLRecord(name, unit), _value(value), _valAsSum(false) {};
   // ~SenMLRecordTemplate(){};

    T get() {return _value; } ;

    bool asSum() {return this->_valAsSum; };

    bool set(T value, double time = (double)NAN, bool asSum = false)
    {
        this->_value = value; 
        this->_valAsSum = asSum;
        return this->setTime(time);
    };


protected:


private:
    T _value;
    bool _valAsSum;
};

#endif // SENMLRECORDTEMPLATE






