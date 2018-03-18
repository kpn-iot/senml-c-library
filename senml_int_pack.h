#ifndef SENMLINTPACK
#define SENMLINTPACK

#include <senml_pack_t.h>

class SenMLIntPack: public SenMLPackTemplate<int>
{
    public:

        SenMLIntPack(const char* baseName): SenMLPackTemplate(baseName, SENML_UNIT_NONE, NAN) {};
        SenMLIntPack(const char* baseName, SenMLUnit baseUnit): SenMLPackTemplate(baseName, baseUnit, NAN) {};
        SenMLIntPack(const char* baseName, SenMLUnit baseUnit, double baseTime): SenMLPackTemplate(baseName, baseUnit, baseTime) {};

        SenMLIntPack(PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate("", SENML_UNIT_NONE, NAN, callback) {};
        SenMLIntPack(const char* baseName, PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate(baseName, SENML_UNIT_NONE, NAN, callback) {};
        SenMLIntPack(const char* baseName, SenMLUnit baseUnit, PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate(baseName, baseUnit, NAN, callback) {};
        SenMLIntPack(const char* baseName, SenMLUnit baseUnit, double baseTime, PACK_ACTUATOR_SIGNATURE): SenMLPackTemplate(baseName, baseUnit, baseTime, callback){};



        ~SenMLIntPack(){};

    protected:

        //when a base value is defined, this function is used by the records to try and
        //adjust their value before writing it to the stream.
        //pack objects from a template override this so they can adjust values.
        virtual void adjustForBaseValue(void* value, SenMLDataType dataType);

        virtual void fieldsToJson();

        virtual void fieldsToCbor();

    private:
};

#endif // SENMLINTPACK