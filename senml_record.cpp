#include <senml_record.h>
#include <senml_helpers.h>
#include <senml_pack.h>
#include <cbor.h>
#include <senml_logging.h>

SenMLRecord::SenMLRecord(const char* name): _name(name), _unit(SENML_UNIT_NONE), _time(NAN), _updateTime(0)
{
    
}

SenMLRecord::SenMLRecord(const char* name, SenMLUnit unit): _name(name), _unit(unit), _time(NAN), _updateTime(0)
{
}

bool SenMLRecord::setTime(double value, bool absolute)
{
    if(absolute){
        SenMLBase* root = this->getRoot();
        if(root && root->isPack()){
            double baseTime = ((SenMLPack*)root)->getBaseTime();
            if(!isnan(baseTime))
                value -= baseTime;
        }
    }
    this->_time = value;
    return true;
}

void SenMLRecord::contentToJson()
{
    printText("{", 1);
    this->fieldsToJson();
    printText("}", 1);
}

void SenMLRecord::adjustToBaseTime(double prev, double time)
{
    if(!isnan(prev))
        this->_time += prev;
    if(!isnan(time))
            this->_time -= time;
}

void SenMLRecord::fieldsToJson()
{
    printText("\"n\":\"", 5);
    printText(this->_name.c_str(), this->_name.length());
    printText("\"", 1);
    if(!isnan(this->_time)){
        printText(",\"t\":", 5);
        printDouble(this->_time, SENML_MAX_DOUBLE_PRECISION);
    }
    if(this->_unit != SENML_UNIT_NONE){
        printText(",\"u\":\"", 6);
        printUnit(this->_unit);
        printText("\"", 1);
    }
    if(this->_updateTime != 0){
        printText(",\"ut\":", 5);
        #ifdef __MBED__
            char buf[10];
            sprintf(buf, "%d", this->_updateTime);
            String val = buf;
        #else
            String val(this->_updateTime);
        #endif
        printText(val.c_str(), val.length());
    }
}

void SenMLRecord::actuate(const void* value, int dataLength, SenMLDataType dataType)
{
    log_debug(this->getName());
    log_debug("no actuator");
}

void SenMLRecord::contentToCbor()
{
    cbor_serialize_map(this->getFieldLength());
    this->fieldsToCbor();
}

int SenMLRecord::getFieldLength()
{
    int result = 2;                                 //always have 1 item for the value and 1 for the name
    if(!isnan(this->_time)) result++;
    if(this->_unit != SENML_UNIT_NONE) result++;
    if(this->_updateTime != 0) result ++;
    return result;
}

void SenMLRecord::fieldsToCbor()
{
    cbor_serialize_int(SENML_CBOR_N_LABEL);
    cbor_serialize_unicode_string(this->_name.c_str());
    if(!isnan(this->_time)){
        cbor_serialize_int(SENML_CBOR_T_LABEL);
        cbor_serialize_double(this->_time);
    }
    if(this->_unit != SENML_UNIT_NONE){
        cbor_serialize_int(SENML_CBOR_U_LABEL);
        cbor_serialize_unicode_string(senml_units_names[this->_unit]);
    }
    if(this->_updateTime != 0){
        cbor_serialize_int(SENML_CBOR_UT_LABEL);
        cbor_serialize_int(this->_updateTime);
    }
}






