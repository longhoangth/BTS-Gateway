/**
 * @file http.cpp
 * @author long (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "http.h"

httplib::Client     clientPost(EDGEX, EDGEX_PORT_POST);
httplib::Client     clientGetTypePos(EDGEX, EDGEX_PORT_GET_TYPE_POS);
httplib::Client     clientGetList(EDGEX, EDGEX_PORT_GET_LIST);

const char          *ping = "PONG";
const char          *path_GET;
const char          *path_POST;
const char          *message_payload_cstr;
int                 value_integer;
static int          run = 1;

http::http(httplib::Client *client, std::string host, int port)
{
    this->client = client;
    this->host = host;
    this->port = port;
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string http::getHost() 
{
    return this->host;
}

/**
 * @brief 
 * 
 * @return int 
 */
int http::getPort()
{
    return this->port;
}

/**
 * @brief 
 * 
 * @return int 
 */
int http::doPING(const char* path)
{
    auto res = this->client->Get(path);
    if(res == nullptr) 
        return 0;
    int status_code = res->status;
    return status_code;
}

/**
 * @brief http method get
 * 
 * @param path 
 * @return std::string 
 */
std::string http::doGET(const char* path)
{
    std::string body_get;
    // LOG(HTTP_GET, {
    //     "URL:" + (std::string)(path)
    // });
    auto res = this->client->Get(path);
    if(res == nullptr)
        return "";

    // LOG(HTTP_RESPONSE, {
    //     "Code: " + to_string(res->status),
    //     "Body: " + res->body
    // });
    body_get = res->body;
    return body_get;
}

/**
 * @brief http method post
 * 
 * @param path 
 * @param body 
 * @param content_type 
 */
std::string http::doPOST(const char* path, std::string body, const std::string content_type)
{
    std::string body_response_post;
    // LOG(HTTP_POST, {
    //     "URL:" + (std::string)(path)
    // });
    auto res = this->client->Post(path, body, content_type);
    if(res == nullptr)
        return "";

    // LOG(HTTP_RESPONSE, {
    //     "Code: " + to_string(res->status),
    //     "Body: " + res->body
    // });
    body_response_post = res->body;
    return body_response_post;
}

/**
 * @brief running the http client
 * 
 */
void Http_run()
{
    // while(httpClientGetTypePos.doPING(URL_EDGEX_PING) == 0){
    //     sleep(3);
    // }
}
