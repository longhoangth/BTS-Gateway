#include "bts_json.h"
#include "bts_debug.h"

// static std::string      message_payload_str;
static char             message_payload_cstr[128];
// data_format_uint16_bytes input;
static DebugLogger      BtsDebugLog;

/**
   @brief Json Parser function

   @param json string input
   @return Json::Value
*/
Json::Value parseJSON(std::string input) {
  //insertion
  Json::Reader     reader;
  Json::Value      root;
  Json::FastWriter writer;
  try{
  reader.parse(input, root);
  }
  catch(const std::exception &e) {
    #if ENA_LIB_LOG
    PLOG_ERROR << "JSON parsing error!";
    PLOG_ERROR << e.what();
    #else
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
    #endif
  }
  return root;
}

/**
   @brief Create modbus pin message
    position and value are got from registers
   {
    "address": pinNum-th
    "position": x,
    "field": field name 
    "value": y
   }
   @return const char* : message to publish
*/
char* Create_modbus_pin_data_message( uint8_t pinNum_th, uint8_t position, uint16_t value)
{
  DebugLogger       DebugLog;
  uint16_t          value_integer;
  float             value_float;
  Json::Reader      reader;
  Json::Value       root;
  Json::FastWriter  writer;
  std::string       message_payload_str;
  uint8_t           payload_flag = 0;

  root[JSON_KEY_1] = pinNum_th;
  root[JSON_KEY_4] = pinNum_th;

  switch (position)
  {
    case MODBUS_PIN_CURRENT:
      value_float = value / 100;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_CURRENT];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VOLTAGE:
      value_float = value / 100;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VOLTAGE];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_SOC:
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_SOC];
      root[JSON_KEY_3] = value;
      payload_flag = 1;
      break;
    case MODBUS_PIN_SOH:
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_SOH];
      root[JSON_KEY_3] = value;
      payload_flag = 1;
      break;
    case MODBUS_PIN_CAPACITY_REMAIN:
      value_float = value / 100;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_CAPACITY_REMAIN];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_CAPACITY_FULL:
      value_float = value / 100;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_CAPACITY_FULL];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_CYCLES:
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_CYCLES];
      root[JSON_KEY_3] = value;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_01:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_01];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_02:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_02];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_03:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_03];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_04:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_04];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_05:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_05];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_06:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_06];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_07:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_07];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_08:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_08];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_09:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_09];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_10:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_10];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_11:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_11];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_12:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_12];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_VCELL_13:
      value_float = value / VCELL;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_VCELL_13];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_TCELL_01:
      value_float = value / 10;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_TCELL_01];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_TCELL_02:
      value_float = value / 10;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_TCELL_02];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_TCELL_03:
      value_float = value / 10;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_TCELL_03];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_TCELL_04:
      value_float = value / 10;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_TCELL_04];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_T_MOSFET:
      value_float = value / 10;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_T_MOSFET];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    case MODBUS_PIN_T_ENV:
      value_float = value / 10;
      root[JSON_KEY_2] = modbus_register_dict_str[MODBUS_PIN_T_ENV];
      root[JSON_KEY_3] = value_float;
      payload_flag = 1;
      break;
    default:
      payload_flag = 0;
      break;
  }
  if(payload_flag) {
    message_payload_str = writer.write(root);
    strcpy(message_payload_cstr,  message_payload_str.c_str());
    BtsDebugLog.DebugLOG(PIN_DATA, {
      "Type: PIN",
      "Pin number: " + std::to_string(pinNum_th),
      "Content: " + message_payload_str
    });
  }
  return message_payload_cstr;
}

/**
 * @brief Create modbus sensor messages 
 * 
 * @param deviceAddress 
 * @param sensor_data 
 * @param index 
 * @return const char* 
 */
char* Create_sensor_float_message( uint8_t deviceAddress, float sensor_data, uint8_t index)
{
    Json::Reader     reader;
    Json::Value      root;
    Json::FastWriter writer;
    std::string      message_payload_str;

    root[JSON_KEY_1] = index + 1 + SENSOR_OFFSET;
    root[JSON_KEY_2] = JSON_VALUE_2;
    root[JSON_KEY_3] = sensor_data;
    root[JSON_KEY_4] = deviceAddress;

    message_payload_str = writer.write(root);
    strcpy(message_payload_cstr,  message_payload_str.c_str());
    BtsDebugLog.DebugLOG(SENSOR_DATA, {
        "Type: Sensor",
        "Content: " + message_payload_str
    });
    return message_payload_cstr;
}

/**
 * @brief Create modbus device messages
 * 
 * @param deviceAddress
 * @param device_data 
 * @param index 
 * @return const char* 
 */
char* Create_device_integer_message( uint8_t deviceAddress, uint8_t device_data, uint8_t index)
{
    Json::Reader     reader;
    Json::Value      root;
    Json::FastWriter writer;
    std::string      message_payload_str;

    root[JSON_KEY_1] = index + 1 + DEVICE_OFFSET;
    root[JSON_KEY_2] = JSON_VALUE_2;
    root[JSON_KEY_3] = device_data;
    root[JSON_KEY_4] = deviceAddress;

    message_payload_str = writer.write(root);
    BtsDebugLog.DebugLOG(DEVICE_DATA, {
        "Type: Device",
        "Content: " + message_payload_str
    });
    strcpy(message_payload_cstr,  message_payload_str.c_str());
    return message_payload_cstr;
}