/**
 * @file mqtt.cpp
 * @author long (longzil193@gmail.com)
 * @brief mqtt source file
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "mqtt.h"

/**
 * @brief Construct a new mqtt http::mqtt http object
 * 
 * @param id 
 * @param host 
 * @param port 
 */
mqtt::mqtt(const char *id, const char *host, int port, int keepalive)
{
    this->id = id;
    this->host = host;
    this->port = port;
    this->keepalive = keepalive;
    int err = mosquitto_lib_init();
    mosq = mosquitto_new(id, true, NULL);
}

/**
 * @brief Destroy the mqtt http::mqtt object
 * 
 */
mqtt::~mqtt()
{
    mosquitto_destroy(this->mosq);
    int err = mosquitto_lib_cleanup();
}

void mqtt::setID(const char *id) {
    this->id = id;
}

void mqtt::setHost(const char *host) {
    this->host = host;
}

void mqtt::setPort(int port) {
    this->port = port;
}

void mqtt::setKeepAlive(int keepalive) {
    this->keepalive = keepalive;
}

/**
 * @brief set connection for mqtt client
 * 
 */
std::string mqtt::run(void)
{   
    int err = mosquitto_connect(this->mosq, this->host, this->port, this->keepalive);
    if(err != 0) {
        exit(0);
    }
    return check(err);
}

/**
 * @brief get mqtt client
 * 
 * @return struct mosquitto* 
 */
struct mosquitto* mqtt::getCLIENT()
{
    return this->mosq;
}

/**
 * @brief mqtt subcribe
 * 
 * @param topic 
 */
std::string mqtt::subscribe(const char *topic)
{
    int err = mosquitto_subscribe(this->mosq, NULL, topic, 0);
    
    return check(err);
}

/**
 * @brief mqtt publish
 * 
 * @param topic 
 * @param msg 
 */
std::string mqtt::send(const char * topic, const char * msg)
{
    int err = mosquitto_publish(this->mosq, NULL, topic, strlen(msg), msg, 0, false);

    return check(err);
}

/**
 * @brief check mqtt return code 
 * 
 * @param err 
 * @return std::std::string 
 */
std::string mqtt::check(int err){
    std::string return_code;
    switch(err){
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
 * @brief using in switch case within callbacks function
 * 
 * @param topic 
 * @return int 
 */
int Topic_converter(std::string topic)
{
    if (topic == SUB_REQ_PING)
    {
        return REQ_PING;
    }
    if (topic == SUB_REQ_CONTROL_TYPE)
    {
        return REQ_CONTROL;
    }
    if (topic == SUB_REQ_CONTROL_VALUE)
    {
        return REQ_CONTROL;
    }
    if (topic == SUB_REQ_CONTROL_NAME)
    {
        return REQ_CONTROL;
    }
    if (topic == SUB_REQ_CONTROL_POSITION)
    {
        return REQ_CONTROL;
    }

    if (topic == SUB_REQ_GET_TYPE)
    {
        return REQ_GET_TYPE;
    }
    if (topic == SUB_REQ_GET_LIST)
    {
        return REQ_GET_LIST;
    }
    if (topic == SUB_REQ_GET_POSITION)
    {
        return REQ_GET_POSITION;
    }
    return -1;
}


