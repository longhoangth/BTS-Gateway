#ifndef GOOGLETES_JSON_TEST_H
#define GOOGLETES_JSON_TEST_H

#include "json/json.h"
#include "register.h"
#include <cstring>

#define json_string_test_control    "{\"position\":53,\"value\":255}\n"
#define json_string_test_update     "{\"field\":\"value\",\"position\":53,\"value\":255}\n"

#define JSON_KEY_1              "position"
#define JSON_KEY_2              "field"
#define JSON_KEY_3              "value"

#define JSON_VALUE_2            "value"

#define DEVICE_OFFSET           50
#define SENSOR_OFFSET           150

Json::Value parseJSON(std::string input);
std::string Create_sensor_float_message( float, uint8_t );
std::string Create_device_integer_message( uint8_t, uint8_t );
Json::Value Create_modbus_0x25_message( uint8_t , uint16_t );

#endif 