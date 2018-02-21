#include "senml_actuator_parser.h"
#include "senml_helpers.h"
#include "JsonListener.h"

#define NONE 0
#define BN_VALUE 1
#define BU_VALUE 2
#define N_VALUE 3
#define V_VALUE 4
#define VB_VALUE 5
#define VD_VALUE 6
#define VS_VALUE 7


void ActuatorListener::key(String key) {
    //Serial.println("key: " + key);
    this->expected = NONE;
    if(key.length() > 0){                  //using faseter char comare instead of string compare
        char first = key.charAt(0);    
        switch (first)
        {
            case 'b':
                if(key.length() == 2){
                    switch (key.charAt(1))
                    {
                        case 'n': this->expected = BN_VALUE; break;
                        case 'u': this->expected = BU_VALUE; break;
                    }
                }
                break;
            case 'n':
                this->expected = N_VALUE; break;
            case 'v':
                if(key.length() == 2){
                    switch (key.charAt(1))
                    {
                        case 'b': this->expected = VB_VALUE; break;
                        case 'd': this->expected = VD_VALUE; break;
                        case 's': this->expected = VS_VALUE; break;
                    }
                }
                else if(key.length() == 1)
                    this->expected = V_VALUE;
                break;
        }
    }
  
}

void ActuatorListener::value(String value) {
    //Serial.println("value: " + value);
    switch (this->expected)
    {
        case BN_VALUE: this->setCurrentPack(value); break;
        case BU_VALUE: this->checkBaseUnit(value); break;
        case N_VALUE: this->setCurrentRecord(value); break;
        case V_VALUE: this->setValue(value, SENML_TYPE_NR); break;
        case VB_VALUE: this->setValue(value, SENML_TYPE_BOOL); break;
        case VD_VALUE: this->setValue(value, SENML_TYPE_DATA); break;
        case VS_VALUE: this->setValue(value, SENML_TYPE_STRING); break;
  }
}

/*
void ActuatorListener::whitespace(char c) {
    Serial.println("whitespace");
}

void ActuatorListener::startDocument() {
    Serial.println("start document");
}

void ActuatorListener::endArray() {
  Serial.println("end array. ");
}

void ActuatorListener::endObject() {
  Serial.println("end object. ");
}

void ActuatorListener::endDocument() {
  Serial.println("end document. ");
}

void ActuatorListener::startArray() {
   Serial.println("start array. ");
}

void ActuatorListener::startObject() {
   Serial.println("start object. ");
}
*/

void ActuatorListener::setCurrentPack(String& name)
{
    this->curPack = NULL;                                                   //reset before we start so we indicate that nothing was ound
    this->curPackName = name;                                               //need a ref to the name in case we can't find the pack object

    if(name == this->root->getBaseName()){                                  //check the root first, most common probably
        this->curPack == this->root;
        return;
    }
    SenMLBase* found = this->root->getFirst();
    while(found){
        if(found->isPack() && name == ((SenMLPack*)found)->getBaseName()){
            this->curPack = (SenMLPack*)found;
            return;
        }
        found = found->getNext();
    }
}

void ActuatorListener::checkBaseUnit(String& name)
{
    if(!(this->curPack && name == senml_units_names[this->curPack->getBaseUnit()]))
        log_debug("bu doesn't match");
}

void ActuatorListener::setCurrentRecord(String& name)
{
    this->curRec = NULL;
    this->curRecName = name;
    if(this->curPack){
        SenMLBase* rec = this->curPack->getFirst();
        while(rec){
            if(rec->isPack() == false &&  name == ((SenMLRecord*)rec)->getName()){
                this->curRec = (SenMLRecord*)rec;
                return;
            }
            rec = rec->getNext();
        }
    }
}

void ActuatorListener::setValue(String& value, SenMLDataType dataType)
{
    if(this->curRec){
        this->curRec->actuate(value.c_str(), dataType);
    }
    else {
        SenMLPack* pack = this->curPack;
        if(!pack)
            pack = this->root;
        if(pack)
            pack->actuate(this->curPackName.c_str(), this->curRecName.c_str(), value.c_str(), dataType);
    }
}