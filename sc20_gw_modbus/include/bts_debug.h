#ifndef _BTSDEBUG_H_
#define _BTSDEBUG_H_

#include "main.h"
/* DEBUG for file bts_get_message */
#define ENABLE_DEBUG_GETMESSAGE_FSM 0

/* DEBUG for file bts_frame_message */
#define ENABLE_DEBUG_FRAME_MESSAGE_ERROR 0
#define ENABLE_DEBUG_FRAME_MESSAGE_STATUS 1

/* DEBUG for file bts_system */
#define ENABLE_DEBUG_SYSTEM_ERROR 1
#define ENABLE_DEBUG_SYSTEM_STATUS 1

/* DEBUG for file bts_system */
#define ENABLE_DEBUG_MODBUS_ERROR 1
#define ENABLE_DEBUG_MODBUS_STATUS 1

/* DEBUG for file message */
#define DEBUG_FILE      0
#define DEBUG_CONSOLE   1
#define DEBUG_MQTT      0
#define DEBUG_SENSOR    0
#define DEBUG_DEVICE    0
#define DEBUG_PIN       0
#define DEBUG_CONTROL   1

enum{
    SENSOR_DATA = 0,
    DEVICE_DATA,
    PIN_DATA,
    CONTROLLER,
    MQTT_PROTOCOL
};

class DebugLogger
{
public:
    void DebugError(const char *str);
    void DebugStatus(const char *str);
    void DebugLOG(int header, std::vector<std::string> content);
private:
   
};
#endif 
