#ifndef SENMLDOUBLEPACK
#define SENMLDOUBLEPACK

#include <senml_pack_t.h>

class SenMLDoublePack: public SenMLPackTemplate<int>
{
    public:

        SenMLDoublePack(const char* baseName): SenMLPackTemplate(baseName, SENML_UNIT_NONE, NAN) {};
        SenMLDoublePack(const char* baseName, SenMLUnit baseUnit): SenMLPackTemplate(baseName, baseUnit, NAN) {};
        SenMLDoublePack(const char* baseName, SenMLUnit baseUnit, double baseTime): SenMLPackTemplate(baseName, baseUnit, baseTime) {};

        SenMLDoublePack(PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate("", SENML_UNIT_NONE, NAN, callback) {};
        SenMLDoublePack(const char* baseName, PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate(baseName, SENML_UNIT_NONE, NAN, callback) {};
        SenMLDoublePack(const char* baseName, SenMLUnit baseUnit, PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate(baseName, baseUnit, NAN, callback) {};
        SenMLDoublePack(const char* baseName, SenMLUnit baseUnit, double baseTime, PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate(baseName, baseUnit, baseTime, callback){};



        ~SenMLDoublePack(){};

    protected:

        //when a base value is defined, this function is used by the records to try and
        //adjust their value before writing it to the stream.
        //pack objects from a template override this so they can adjust values.
        virtual void adjustForBaseValue(void* value, SenMLDataType dataType);

        virtual void fieldsToJson();

        virtual void fieldsToCbor();

    private:
};

#endif // SENMLDOUBLEPACK