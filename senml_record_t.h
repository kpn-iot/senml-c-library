#ifndef SENMLRECORDTEMPLATE
#define SENMLRECORDTEMPLATE

#include <senml_record.h>



template <class T>
class SenMLRecordTemplate: public SenMLRecord
{
public:
    SenMLRecordTemplate(const char* name): SenMLRecord(name){};
    SenMLRecordTemplate(const char* name, SenMLUnit unit):  SenMLRecord(name, unit){};
    SenMLRecordTemplate(const char* name, SenMLUnit unit, T value):  SenMLRecord(name, unit), _value(value) {};
   // ~SenMLRecordTemplate(){};

    T get() {return _value; } ;

    bool set(T value, double time = (double)NAN)
    {
        this->_value = value; 
        return this->setTime(time);
    };

protected:


private:
    T _value;
};

#endif // SENMLRECORDTEMPLATE






