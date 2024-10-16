#ifndef _MAIN_H_
#define _MAIN_H_

#include <ctime>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <set>

#define ENA_LIB_JSON    1
#define ENA_LIB_MQTT    1
#define ENA_LIB_MODBUS  1
#define ENA_LIB_LOG     1

#if ENA_LIB_LOG
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#endif

#if   ENA_LIB_JSON
#include <jsoncpp/json/json.h>
#else
//#include "json/json.h"
#endif

#if ENA_LIB_MODBUS
#include <modbus/modbus.h>
#endif

#if ENA_LIB_MQTT
#include <mqtt_protocol.h>
#include <mosquitto.h>
#else
#include "mqtt_protocol.h"
#include "mosquitto.h"
#endif

#include "bts_debug.h"
#include "bts_modbus.h"
#include "bts_json.h"
#include "bts_mqtt.h"
#include "bts_register.h"

#define RETRUN_ERROR -1

#define PortModBusName      "/dev/ttyUSB1"
#define BaudRateModBus      9600

#define ByteToInt16(a, b)   ((a<<8)|(b))

#define MB_DEVICE_ADDRESS       		0x30
#define MB_DEVICE_REG_CONTROL   		80

/*10 Cam bien - 20(lan doc)*2(2byte) = 40byte */
#define MB_DEVICE_REG_READ_SENSOR_START 0
#define MB_DEVICE_REG_READ_SENSOR_END   20

/*40 Trang thai - 20(lan doc)*2(2byte) = 40byte */
#define MB_DEVICE_REG_READ_STATUS_START 20
#define MB_DEVICE_REG_READ_STATUS_END   20

#define MB_DEVICE_REG_READ_PIN_START    0
#define MB_DEVICE_REG_READ_PIN_END      0x25

typedef union 
{
	float data_float;
	uint16_t bytes[2];	
} data_format_float_uint16;

typedef enum 
{
	FSM_STATE_START        		= 0,
	FSM_STATE_READ_SENSOR  		= 1,
	FSM_STATE_READ_STATUS  		= 2,
	FSM_STATE_READ_PIN     		= 3,
	FSM_STATE_READ_END     		= 4,
}fsmReadModbus_e;

#endif /* _MAIN_H_ */
