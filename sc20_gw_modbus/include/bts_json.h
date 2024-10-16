/**
 * @file json.h
 * @author long (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifndef _BTS_JSON_H_
#define _BTS_JSON_H_

#include "main.h"

#define JSON_KEY_1      "position"
#define JSON_KEY_2      "field"
#define JSON_KEY_3      "value"  
#define JSON_KEY_4      "address"

#define JSON_VALUE_2    "value"

#define DEVICE_OFFSET   100
#define SENSOR_OFFSET   50

typedef union
{
    uint16_t data_uint16;
    uint8_t bytes[2];
} data_format_uint16_bytes;

#if ENA_LIB_JSON
class CustomJson {
    public:

    private:

};

Json::Value parseJSON(std::string input);
#endif
char* Create_modbus_pin_data_message( uint8_t, uint8_t, uint16_t);
char* Create_sensor_float_message( uint8_t, float, uint8_t );
char* Create_device_integer_message( uint8_t, uint8_t, uint8_t );

#endif