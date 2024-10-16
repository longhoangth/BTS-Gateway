/**
 * @file mqtt.h
 * @author long (longzil193@gmail.com)
 * @brief mqtt uart header file
 * @version 0.1
 * @date 2023-02-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _MQTTs_H_
#define _MQTTs_H_

#include "main.h"
#define MQTT_HOST           "Mqtt.mysignage.vn"
// #define MQTT_HOST           "localhost"
#define MQTT_PORT           1883
#define CLIENT_ID_MODBUS    "modbus_mqtt"
#define CLIENT_ID_MODBUS_1  "modbus_mqtt_1"
/*  modbus  */
#define SUB_CONTROL_DEVICE  "gw/modbus/control/device"
#define SUB_CONTROL_PIN     "gw/modbus/control/pin"
#define SUB_CONTROL         "gw/modbus/control"
#define SUB_ENABLE_MODBUS   "gw/modbus/enable"
#define PUB_LOG_MODBUS      "gw/log/modbus"
#define PUB_UPDATE_MODBUS   "gw/device/update/modbus"

enum topics {   
    MQTT_CONTROL_DEVICE = 0,
    MQTT_CONTROL_PIN,
    MQTT_ENABLE_MODBUS,
    MQTT_CONTROL,
};

/*------------------------------------------------------------------------------*/
class Mqtt
{
    private:
        struct mosquitto    *mosq = NULL;
        const char          *id;
        const char          *host;
        int                 port;
        int                 keepalive;

    public:
        Mqtt();
        void Init(const char *id, const char *host, int port = 1883, int keepalive = 60);
        ~Mqtt();
        void Destroy(void);
        struct mosquitto* GetCLIENT(void);
        void Run(void);
        void Rerun(void);
        void Send(const char * topic, const char * msg);
        void Subscribe(const char * topic);
        std::string Check(int err);
};

/*------------------------------------------------------------------------------*/

int Topic_converter( std::string);

/*------------------------------------------------------------------------------*/
#endif /* MQTT */
