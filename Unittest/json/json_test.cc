#include "json_test.h"

static Json::Reader     reader;
static Json::Value      root;
static Json::FastWriter writer;
static std::string      message_payload_str;

/**
 * @brief Json Parser function
 * 
 * @param input 
 * @return Json::Value 
 */
Json::Value parseJSON(std::string input){
    reader.parse(input, root);
    return root;
}

/**
 * @brief Create sensor messages 
 * 
 * @param dataf 
 * @param start_index 
 * @return std::string 
 */
std::string Create_sensor_float_message( float dataf, uint8_t start_index)
{
    root[JSON_KEY_1] = start_index + 1 + SENSOR_OFFSET;
    root[JSON_KEY_2] = JSON_VALUE_2;
    root[JSON_KEY_3] = dataf;

    message_payload_str = writer.write(root);

    return message_payload_str;
}

/**
 * @brief Create device messages
 * 
 * @param dataI 
 * @param start_index 
 * @return std::string
 */
std::string Create_device_integer_message( uint8_t dataI, uint8_t start_index)
{
    root[JSON_KEY_1] = start_index + 1 + DEVICE_OFFSET;
    root[JSON_KEY_2] = JSON_VALUE_2;
    root[JSON_KEY_3] = dataI;

    message_payload_str = writer.write(root);

    return message_payload_str;
}

/**
 * @brief Create modbus message 
 *  position and value are got from registers 0x25
 * {
 *  "position": x,
 *  "value": y
 * }
 * @return 
 */
Json::Value Create_modbus_0x25_message( uint8_t position, uint16_t value)
{
    uint16_t value_integer;
    float value_float;

    root[JSON_KEY_1] = PIN_NUMBER;

    switch (position)
    {
    case CURRENT:
        value_float = value/1000;
        root[JSON_KEY_2] = modbus_register_dict_str[CURRENT];
        root[JSON_KEY_3] = value_float;
        break;
    case VOLTAGE:
        value_float = value/100;
        root[JSON_KEY_2] = modbus_register_dict_str[VOLTAGE];
        root[JSON_KEY_3] = value_float;
        break;
    case SOC:
        root[JSON_KEY_2] = modbus_register_dict_str[SOC];
        root[JSON_KEY_3] = value;
        break;
    case SOH:
        root[JSON_KEY_2] = modbus_register_dict_str[SOH];
        root[JSON_KEY_3] = value;
        break;
    case CAPACITY_REMAIN:
        value_float = value/1000;
        root[JSON_KEY_2] = modbus_register_dict_str[CAPACITY_REMAIN];
        root[JSON_KEY_3] = value_float;
        break;
    case CAPACITY_FULL:
        value_float = value/1000;
        root[JSON_KEY_2] = modbus_register_dict_str[CAPACITY_FULL];
        root[JSON_KEY_3] = value_float;
        break;
    case CYCLES:
        root[JSON_KEY_2] = modbus_register_dict_str[CYCLES];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_01:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_01];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_02:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_02];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_03:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_03];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_04:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_04];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_05:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_05];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_06:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_06];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_07:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_07];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_08:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_08];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_09:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_09];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_10:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_10];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_11:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_11];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_12:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_12];
        root[JSON_KEY_3] = value;
        break;
    case VCELL_13:
        
        root[JSON_KEY_2] = modbus_register_dict_str[VCELL_13];
        root[JSON_KEY_3] = value;
        break;
    case TCELL_01:
        value_float = value/10;
        root[JSON_KEY_2] = modbus_register_dict_str[TCELL_01];
        root[JSON_KEY_3] = value_float;
        break;
    case TCELL_02:
        value_float = value/10;
        root[JSON_KEY_2] = modbus_register_dict_str[TCELL_02];
        root[JSON_KEY_3] = value_float;
        break;
    case TCELL_03:
        value_float = value/10;
        root[JSON_KEY_2] = modbus_register_dict_str[TCELL_03];
        root[JSON_KEY_3] = value_float;
        break;
    case TCELL_04:
        value_float = value/10;
        root[JSON_KEY_2] = modbus_register_dict_str[TCELL_04];
        root[JSON_KEY_3] = value_float;
        break;
    case T_MOSFET:
        value_float = value/10;
        root[JSON_KEY_2] = modbus_register_dict_str[T_MOSFET];
        root[JSON_KEY_3] = value_float;
        break;
    case T_ENV:
        value_float = value/10;
        root[JSON_KEY_2] = modbus_register_dict_str[T_ENV];
        root[JSON_KEY_3] = value_float;
        break;
    default:
        break;
    }

    return root;
}