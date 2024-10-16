/**
 * @file mqtt.h
 * @author long (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#ifndef _MQTT_H_
#define _MQTT_H_

/*------------------------------------------------------------------------------*/

#include <mosquitto.h>
#include <cstring>
#include <stdint.h>
#include <ostream>
#include <json/json.h>
#include <string>

#define CLIENT_ID               "client_test"
#define MQTT_HOST               "Remote.mysignage.vn"
#define MQTT_PORT               1883


#define URL_EDGEX_PING          "/api/v1/ping"
#define URL_EDGEX_PATTERN       "/api/v1/resource/"
#define CONTENT_TYPE            "text/plain"

/* subcribe topics definitions */
#define SUBCRIBE_TOPIC              "test"

#define SUB_REQ_PING                "gw/request/ping"
#define SUB_REQ_GET_TYPE            "gw/request/get/type"
#define SUB_REQ_GET_LIST            "gw/request/get/list"
#define SUB_REQ_CONTROL_NAME        "gw/request/control/name"
#define SUB_REQ_CONTROL_TYPE        "gw/request/control/type"
#define SUB_REQ_GET_POSITION        "gw/request/get/position"
#define SUB_REQ_CONTROL_VALUE       "gw/request/control/value"
#define SUB_REQ_CONTROL_POSITION    "gw/request/control/position"

/* publish topics definitions */
#define PUB_DEVICE_PING             "gw/device/pong"
#define PUB_MQTT_CONTROL_PING       "gw/mqtt_control/pong"
#define PUB_GW_DEVICE_POST_TYPE     "gw/device/post/type"
#define PUB_GW_DEVICE_POST_LIST     "gw/device/post/list"
#define PUB_GW_DEVICE_POST_POSITION "gw/device/post/position"

#define MOSQ_ERR_SUCCESS_STR         "MOSQ_ERR_SUCCESS"


enum MQTTtopics
{
    REQ_PING = 0,
    REQ_CONTROL,
    REQ_CONTROL_TYPE,
    REQ_CONTROL_VALUE,
    REQ_CONTROL_NAME,
    REQ_CONTROL_POSITION,
    REQ_GET_POSITION,
    REQ_GET_TYPE,
    REQ_GET_LIST,
    DEVICE_PING,
    MQTT_CONTROL_PING,
    DEVICE_POST_TYPE,
    DEVICE_POST_LIST,
    DEVICE_POST_POSITION,
};

/*------------------------------------------------------------------------------*/

class mqtt
{
    private:
        struct mosquitto    *mosq = NULL;
        const char          *id;
        const char          *host;
        int                 port;
        int                 keepalive;

    public:
        mqtt();
        mqtt(const char *id, const char *host, int port = 1883, int keepalive = 60);
        ~mqtt();
        void setID(const char *id);
        void setHost(const char *host);
        void setPort(int port);
        void setKeepAlive(int keepalive);
        struct mosquitto* getCLIENT();
        std::string run(void);
        std::string send(const char * topic, const char * msg);
        std::string subscribe(const char * topic);
        std::string check(int err);
};

/*------------------------------------------------------------------------------*/

int Topic_converter(std::string topic);

/*------------------------------------------------------------------------------*/

#endif /* MQTT */
