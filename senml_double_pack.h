#ifndef SENMLDOUBLEPACK
#define SENMLDOUBLEPACK

#include <senml_pack_t.h>

class SenMLDoublePack: public SenMLPackTemplate<double>
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

        virtual void setupStreamCtx(Stream *dest, SenMLStreamMethod format);
        virtual void setupStreamCtx(char *dest, int length, SenMLStreamMethod format);

        virtual void fieldsToJson();

        virtual void fieldsToCbor();

    private:
};

#endif // SENMLDOUBLEPACK






