#include <senml_record.h>
#include <senml_helpers.h>
#include <senml_pack.h>
#include <cbor.h>

SenMLRecord::SenMLRecord(const char* name): SenMLRecord(name, SENML_UNIT_NONE)
{
    
}

SenMLRecord::SenMLRecord(const char* name, SenMLUnit unit): _name(name), _unit(unit), _time(NAN)
{
}

bool SenMLRecord::setTime(double value, bool absolute)
{
    if(absolute){
        SenMLBase* root = this->getRoot();
        if(root && root->isPack()){
            SenMLPack* pack = (SenMLPack*)root;
            double baseTime = ((SenMLPack*)root)->getBaseTime();
            if(!isnan(baseTime))
                value -= baseTime;
        }
    }
    this->_time = value;
}

void SenMLRecord::toJson(Stream *dest)
{
    dest->print("{");
    this->fieldsToJson(dest);
    dest->print("}");
}

void SenMLRecord::adjustToBaseTime(double prev, double time)
{
    if(!isnan(prev))
        this->_time += prev;
    if(!isnan(time))
            this->_time -= time;
}

void SenMLRecord::fieldsToJson(Stream *dest)
{
    dest->print("\"n\":\"");
    dest->print(this->_name);
    dest->print("\"");
    if(!isnan(this->_time)){
        dest->print(",\"t\":");
        printDouble(this->_time, 16, dest);
    }
    if(this->_unit != SENML_UNIT_NONE){
        dest->print(",\"u\":\"");
        printUnit(this->_unit, dest);
        dest->print("\"");
    }
}

void SenMLRecord::actuate(const char* value, SenMLDataType dataType)
{
    log_debug(this->getName());
    log_debug("no actuator");
}


int SenMLRecord::getFieldLength()
{
    int result = 2;                                 //always have 1 item for the value and 1 for the name
    if(!isnan(this->_time)) result++;
    if(this->_unit != SENML_UNIT_NONE) result++;
    return result;
}

void SenMLRecord::fieldsToCbor(Stream *dest)
{
    cbor_serialize_int(dest, SENML_CBOR_N_LABEL);
    cbor_serialize_unicode_string(dest, this->_name.c_str());
    if(!isnan(this->_time)){
        cbor_serialize_int(dest, SENML_CBOR_T_LABEL);
        cbor_serialize_double(dest, this->_time);
    }
    if(this->_unit != SENML_UNIT_NONE){
        cbor_serialize_int(dest, SENML_CBOR_U_LABEL);
        cbor_serialize_unicode_string(dest, senml_units_names[this->_unit]);
    }
}