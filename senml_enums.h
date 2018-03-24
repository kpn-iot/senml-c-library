#ifndef SENMLENUMS
#define SENMLENUMS


//data types that the value can have in senml
enum SenMLDataType { //json data types:
                    SENML_TYPE_NR, SENML_TYPE_STRING, SENML_TYPE_BOOL, SENML_TYPE_DATA,
                    //cbor data types, which have already converted the data value
                    CBOR_TYPE_UINT, CBOR_TYPE_INT, CBOR_TYPE_STRING, CBOR_TYPE_FLOAT, CBOR_TYPE_DOUBLE, CBOR_TYPE_BOOL, CBOR_TYPE_DATA
                   };

extern const char* senml_units_names[];

//used by some functions to determine how data should be read/rendered to the stream: in the original format
//or converted to hex values. The latter is used for serial communication with a modem such as a lora modem.
enum SenMLStreamMethod {SENML_HEX, SENML_RAW};

enum SenMLUnit {SENML_UNIT_NONE, 
                SENML_UNIT_METER,
                SENML_UNIT_KILOGRAM,
                SENML_UNIT_GRAM,
                SENML_UNIT_SECOND,
                SENML_UNIT_AMPERE,
                SENML_UNIT_KELVIN,                             
                SENML_UNIT_CANDELA,                            
                SENML_UNIT_MOLE,                               
                SENML_UNIT_HERTZ,                              
                SENML_UNIT_RADIAN,                             
                SENML_UNIT_STERADIAN,                          
                SENML_UNIT_NEWTON,                             
                SENML_UNIT_PASCAL,                             
                SENML_UNIT_JOULE,                              
                SENML_UNIT_WATT,                               
                SENML_UNIT_COULOMB,                            
                SENML_UNIT_VOLT,                             
                SENML_UNIT_FARAD,                              
                SENML_UNIT_OHM,                            
                SENML_UNIT_SIEMENS,
                SENML_UNIT_WEBER,                            
                SENML_UNIT_TESLA,                             
                SENML_UNIT_HENRY,
                SENML_UNIT_DEGREES_CELSIUS,
                SENML_UNIT_LUMEN,                              
                SENML_UNIT_LUX ,                               
                SENML_UNIT_BECQUEREL,                          
                SENML_UNIT_GRAY,                               
                SENML_UNIT_SIEVERT,                            
                SENML_UNIT_KATAL,                      
                SENML_UNIT_SQUARE_METER,
                SENML_UNIT_CUBIC_METER,
                SENML_UNIT_LITER ,
                SENML_UNIT_VELOCITY,
                SENML_UNIT_ACCELERATION,
                SENML_UNIT_CUBIC_METER_PER_SECOND,
                SENML_UNIT_LITER_PER_SECOND,
                SENML_UNIT_WATT_PER_SQUARE_METER,
                SENML_UNIT_CANDELA_PER_SQUARE_METER,
                SENML_UNIT_BIT ,
                SENML_UNIT_BIT_PER_SECOND,
                SENML_UNIT_DEGREES_LATITUDE,
                SENML_UNIT_DEGREES_LONGITUDE,
                SENML_UNIT_PH ,
                SENML_UNIT_DECIBEL ,
                SENML_UNIT_DECIBEL_RELATIVE_TO_1_W,
                SENML_UNIT_BEL ,
                SENML_UNIT_COUNTER,
                SENML_UNIT_RATIO ,
                SENML_UNIT_RELATIVE_HUMIDITY,
                SENML_UNIT_PERCENTAGE_REMAINING_BATTERY_LEVEL,
                SENML_UNIT_SECONDS_REMAINING_BATTERY_LEVEL,
                SENML_UNIT_EVENT_RATE_PER_SECOND,
                SENML_UNIT_EVENT_RATE_PER_MINUTE,
                SENML_UNIT_BPM,
                SENML_UNIT_BEATS,
                SENML_UNIT_SIEMENS_PER_METER
                };

#endif // !SENMLENUMS






