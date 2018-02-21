#include <senml_pack.h>
#include <senml_base.h>
#include <senml_helpers.h>
#include <senml_actuator_parser.h>
#include <JsonStreamingParser.h>
#include <math.h>
#include <cbor.h>



void SenMLPack::setBaseName(const char* name)
{
    this->_bn = name;
}

const char* SenMLPack::getBaseName()
{
    return this->_bn.c_str();
}

void SenMLPack::settBaseUnit(SenMLUnit unit)
{
    this->_bu = unit;
}

SenMLUnit SenMLPack::getBaseUnit()
{
    return this->_bu;
}

void SenMLPack::setBaseTime(double time)
{
    double prev = this->_bt;
    this->_bt = time;                               //set before asking children -> could be better to do it afterwards?
    SenMLBase *item = this->_start;
    while(item){
        item->adjustToBaseTime(prev, time);
        item = item->getNext();
    }
}

double SenMLPack::getBaseTime()
{
    return this->_bt;
}

void SenMLPack::setLast(SenMLBase* value)
{
    if(value == this)                           //if we become the last item in the list, then the list is empty.
        this->_end = NULL;
    else
        this->_end = value;
}


bool SenMLPack::add(SenMLBase* item)
{
    if(item->getNext() != NULL){
        log_debug("item already added to list");
        return false;
    }

    SenMLBase* last = this->_end;
    if(last){
        last->setNext(item);
        item->setPrev(last);
    }
    else{
        this->_start = item;
        item->setPrev(this);
    }
    this->_end = item;
}

bool SenMLPack::clear()
{
    SenMLBase *item = this->_start;
    while(item){
        if(item->isPack())                                          //if it's a pack element, it also needs to clear out it's children.
            ((SenMLPack*)item)->clear();
        item->setPrev(NULL);
        SenMLBase *next = item->getNext();
        item->setNext(NULL);
        item = next;
    }
    this->setNext(NULL);
    this->setPrev(NULL);
    this->_end = NULL;
    this->_start = NULL;
}

void SenMLPack::fromJson(Stream *source)
{
    JsonStreamingParser parser;
    ActuatorListener listener(this);
    
    parser.setListener(&listener);
    char data = source->read();
    while(data != -1){
        parser.parse(data); 
    }
    // when we get here, all the data is stored in the document and callbacks have been called.
}

void SenMLPack::fromJson(const char *source)
{
    JsonStreamingParser parser;
    ActuatorListener listener(this);
    
    parser.setListener(&listener);
    for(int i = 0; source[i] != 0; i++){
        parser.parse(source[i]); 
    }
    // when we get here, all the data is stored in the document and callbacks have been called.
}

void SenMLPack::toJson(Stream *dest)
{
    dest->print("[");
    this->contentToJson(dest);
    dest->print("]");
}


void SenMLPack::fieldsToJson(Stream *dest)
{
    dest->print("\"bn\":\"");
    dest->print(this->_bn);
    dest->print("\"");
    if(this->_bu){
        dest->print(",\"bu\":\"");
        printUnit(this->_bu, dest);
        dest->print("\"");
    }
    if(!isnan(this->_bt)){
        dest->print(",\"bt\":");
        printDouble(this->_bt, 16, dest);
    }
}

void SenMLPack::contentToJson(Stream *dest)
{
    dest->print("{");
    this->fieldsToJson(dest);
    SenMLBase *next = this->_start;
    if(next && next->isPack() == false){                        //we can only inline the first record. If the first item is a Pack (child device), then don't inline it.
        dest->print(",");
        next->fieldsToJson(dest);
        next = next->getNext();
    }
    dest->print("}");
    while(next){
        dest->print(",");
        if(next->isPack() == false)
            next->toJson(dest);
        else
            ((SenMLPack*)next)->contentToJson(dest);
        next = next->getNext();
    }
}

void SenMLPack::actuate(const char* pack, const char* record, const char* value, SenMLDataType dataType)
{
    if(this->callback)
        this->callback(pack, record, value, dataType);
}

void SenMLPack::toCbor(Stream *dest)
{
    Serial.println("start cbor");
    cbor_serialize_array(dest, this->getArrayLength());
    this->contentToCbor(dest);
}


void SenMLPack::contentToCbor(Stream *dest)
{
    cbor_serialize_map(dest, this->getFieldLength());

    this->fieldsToCbor(dest);
    SenMLBase *next = this->_start;
    if(next && next->isPack() == false){                        //we can only inline the first record. If the first item is a Pack (child device), then don't inline it.
        next->fieldsToCbor(dest);
        next = next->getNext();
    }

    while(next){
        if(next->isPack() == false)
            next->contentToCbor(dest);
        else
            ((SenMLPack*)next)->contentToCbor(dest);
        next = next->getNext();
    }
}

int SenMLPack::getArrayLength()
{
    int result = 0;                             //init to 0 cause if there is a record, the first will become part of the first element in the array, if we were to init to 1, we would have 1 record too many.
    SenMLBase *next = this->_start;
    while(next){                                //we can only inline the first record. If the first item is a Pack (child device), then don't inline it.
        result += next->getArrayLength();       //custom record implementations may wrap multiple records.
        next = next->getNext();
    }
    if(result == 0)                             //if there are no items in this pack, then we still render 1 array element, that of the pack itself.
        result = 1;
}


int SenMLPack::getFieldLength()
{
    int result = 1;                             //always render the base name
    if(this->_bu) result++;
    if(!isnan(this->_bt)) result++;

    SenMLBase *next = this->_start;
    if(next && next->isPack() == false){        //we can only inline the first record. If the first item is a Pack (child device), then don't inline it.
        result += next->getFieldLength();
        next = next->getNext();
    }
    return result;
}

void SenMLPack::fieldsToCbor(Stream *dest)
{
    cbor_serialize_int(dest, SENML_CBOR_BN_LABEL);
    cbor_serialize_unicode_string(dest, this->_bn.c_str());
    if(this->_bu){
        cbor_serialize_int(dest, SENML_CBOR_BU_LABEL);
        cbor_serialize_unicode_string(dest, senml_units_names[this->_bu]);
    }
    if(!isnan(this->_bt)){
        cbor_serialize_int(dest, SENML_CBOR_BT_LABEL);
        cbor_serialize_double(dest, this->_bt);
    }
}