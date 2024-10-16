/**
   @file mqtt.cpp
   @author long (longzil193@gmail.com)
   @brief mqtt uart source code
   @version 0.1
   @date 2023-02-09

   @copyright Copyright (c) 2023

*/
#include "bts_mqtt.h"

Mqtt::Mqtt() 
{
  DebugLogger DebugLog;
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "Type: Construction"
  });
}

/**
   @brief Initialize a new Mqtt object

   @param id
   @param host
   @param port
   @return void
*/
void Mqtt::Init(const char *id, const char *host, int port, int keepalive)
{
  DebugLogger DebugLog;
  this->id = id;
  this->host = host;
  this->port = port;
  this->keepalive = keepalive;
  mosquitto_lib_init();
  this->mosq = mosquitto_new(this->id, true, NULL);
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "Type: Initialization"
  });
}

/**
   @brief Destroy the mqtt http::mqtt object
*/
Mqtt::~Mqtt()
{
  free(this->mosq);
  DebugLogger DebugLog;
  mosquitto_destroy(this->mosq);
  mosquitto_lib_cleanup();
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "Type: Destruction"
  });
}

/**
 * @brief Destroy the client
 * 
 * @return void
 */
void Mqtt::Destroy(void) 
{
  DebugLogger DebugLog;
  mosquitto_destroy(this->mosq);
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "Type: Destruction"
  });
}

/**
  @brief Set connection for mqtt client

  @return void
*/
void Mqtt::Run(void)
{
  DebugLogger DebugLog;
  int err = mosquitto_connect(this->mosq, this->host, this->port, this->keepalive);
  if (err != 0) {
    DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "MQTT connection failed"
    });
    exit(0);
  }
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "MQTT connection succeeded"
    });
  mosquitto_loop_start(this->mosq);
}

/**
  @brief client reconnect
  @return void
*/
void Mqtt::Rerun(void)
{
  DebugLogger DebugLog;
  int err = mosquitto_reconnect(this->mosq);
  if (err != 0) {
    DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "MQTT connection failed"
    });
    exit(0);
  }
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "MQTT connection succeeded"
    });
  mosquitto_loop_start(this->mosq);
}

/**
   @brief get mqtt client

   @return struct mosquitto*
*/
struct mosquitto* Mqtt::GetCLIENT(void)
{
  return this->mosq;
}

/**
   @brief mqtt subcribe

   @param topic
   @return void - mqtt error code
*/
void Mqtt::Subscribe(const char *topic)
{
  DebugLogger DebugLog;
  int err = mosquitto_subscribe(this->mosq, NULL, topic, 0);
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "Type: Subscription",
    "Code: " + Check(err),
    "Topic: " + (std::string)(topic)
  });
}

/**
   @brief mqtt publish

   @param topic
   @param msg
   @return void - mqtt error code
*/
void Mqtt::Send(const char * topic, const char * msg)
{
  DebugLogger DebugLog;
  int err = mosquitto_publish(this->mosq, NULL, topic, strlen(msg), msg, 0, false);
  #if ENA_LIB_LOG
  if(err != MOSQ_ERR_SUCCESS) {
    PLOG_ERROR << Check(err);
  }
  #else
  DebugLog.DebugLOG(MQTT_PROTOCOL, {
    "Type: Publish",
    "Code: " + Check(err)
  });
  #endif
}

/**
   @brief check mqtt return code

   @param err
   @return mqtt error code - std::std::string
*/
std::string Mqtt::Check(int err) 
{
  std::string return_code;
  switch (err) {
    case MOSQ_ERR_AUTH_CONTINUE:
      return_code = "MOSQ_ERR_AUTH_CONTINUE";
      break;
    case MOSQ_ERR_NO_SUBSCRIBERS:
      return_code = "MOSQ_ERR_NO_SUBSCRIBERS";
      break;
    case MOSQ_ERR_SUB_EXISTS:
      return_code = "MOSQ_ERR_SUB_EXISTS";
      break;
    case MOSQ_ERR_CONN_PENDING:
      return_code = "MOSQ_ERR_CONN_PENDING";
      break;
    case MOSQ_ERR_SUCCESS:
      return_code = "MOSQ_ERR_SUCCESS";
      break;
    case MOSQ_ERR_NOMEM:
      return_code = "MOSQ_ERR_NOMEM";
      break;
    case MOSQ_ERR_PROTOCOL:
      return_code = "MOSQ_ERR_PROTOCOL";
      break;
    case MOSQ_ERR_INVAL:
      return_code = "MOSQ_ERR_INVAL";
      break;
    case MOSQ_ERR_NO_CONN:
      return_code = "MOSQ_ERR_NO_CONN";
      break;
    case MOSQ_ERR_CONN_REFUSED:
      return_code = "MOSQ_ERR_CONN_REFUSED";
      break;
    case MOSQ_ERR_NOT_FOUND:
      return_code = "MOSQ_ERR_NOT_FOUND";
      break;
    case MOSQ_ERR_CONN_LOST:
      return_code = "MOSQ_ERR_CONN_LOST";
      break;
    case MOSQ_ERR_TLS:
      return_code = "MOSQ_ERR_TLS";
      break;
    case MOSQ_ERR_PAYLOAD_SIZE:
      return_code = "MOSQ_ERR_PAYLOAD_SIZE";
      break;
    case MOSQ_ERR_NOT_SUPPORTED:
      return_code = "MOSQ_ERR_NOT_SUPPORTED";
      break;
    case MOSQ_ERR_AUTH:
      return_code = "MOSQ_ERR_AUTH";
      break;
    case MOSQ_ERR_ACL_DENIED:
      return_code = "MOSQ_ERR_ACL_DENIED";
      break;
    case MOSQ_ERR_UNKNOWN:
      return_code = "MOSQ_ERR_UNKNOWN";
      break;
    case MOSQ_ERR_ERRNO:
      return_code = "MOSQ_ERR_ERRNO";
      break;
    case MOSQ_ERR_EAI:
      return_code = "MOSQ_ERR_EAI";
      break;
    case MOSQ_ERR_PROXY:
      return_code = "MOSQ_ERR_PROXY";
      break;
    case MOSQ_ERR_PLUGIN_DEFER:
      return_code = "MOSQ_ERR_PLUGIN_DEFER";
      break;
    case MOSQ_ERR_MALFORMED_UTF8:
      return_code = "MOSQ_ERR_MALFORMED_UTF8";
      break;
    case MOSQ_ERR_KEEPALIVE:
      return_code = "MOSQ_ERR_KEEPALIVE";
      break;
    case MOSQ_ERR_LOOKUP:
      return_code = "MOSQ_ERR_LOOKUP";
      break;
    case MOSQ_ERR_MALFORMED_PACKET:
      return_code = "MOSQ_ERR_MALFORMED_PACKET";
      break;
    case MOSQ_ERR_DUPLICATE_PROPERTY:
      return_code = "MOSQ_ERR_DUPLICATE_PROPER";
      break;
    case MOSQ_ERR_TLS_HANDSHAKE:
      return_code = "MOSQ_ERR_TLS_HANDSHAKE";
      break;
    case MOSQ_ERR_QOS_NOT_SUPPORTED:
      return_code = "MOSQ_ERR_QOS_NOT_SUPPORTED";
      break;
    case MOSQ_ERR_OVERSIZE_PACKET:
      return_code = "MOSQ_ERR_OVERSIZE_PACKET";
      break;
    case MOSQ_ERR_OCSP:
      return_code = "MOSQ_ERR_OCSP";
      break;
    default:
      return_code = "Undefined error code!";
      break;
  }
  return return_code;
}

/**
 * @brief Topic converter function
 * 
 * @param topic 
 * @return int 
 */
int Topic_converter(std::string topic) {
    if(topic == SUB_CONTROL_DEVICE) 
    {
        return MQTT_CONTROL_DEVICE;
    }

    if(topic == SUB_CONTROL_PIN) 
    {
        return MQTT_CONTROL_PIN;
    }

    if(topic == SUB_ENABLE_MODBUS) 
    {
        return MQTT_ENABLE_MODBUS;
    }

    if(topic == SUB_CONTROL)
    {
        return MQTT_CONTROL;
    }
    
    return -1;
}