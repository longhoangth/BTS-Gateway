/**
 * @file http.h
 * @author long (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#ifndef _HTTP_H_
#define _HTTP_H_

/*------------------------------------------------------------------------------*/

#include "httplib.h"
#include <string>
#include <cstring>
#include <unistd.h>

/*------------------------------------------------------------------------------*/

#define EDGEX                   "localhost"
#define EDGEX_PORT_POST         49986
#define EDGEX_PORT_GET_TYPE_POS 48080
#define EDGEX_PORT_GET_LIST     48082
#define URL_EDGEX_PING          "/api/v1/ping"
#define URL_EDGEX_PATTERN       "/api/v1/resource/"
#define CONTENT_TYPE            "text/plain"

/*------------------------------------------------------------------------------*/

class http
{
    private:
        httplib::Client *client;
        std::string     host;
        int             port;
    
    public:
        http(httplib::Client *client, std::string host, int port);
        std::string getHost();
        int getPort();
        int doPING(const char* path);
        std::string doGET(const char* path);
        std::string doPOST(const char* path, std::string body, const std::string content_type = CONTENT_TYPE);
};

/*-----------------------------------------------------------------------------*/

void Http_run();

/*-----------------------------------------------------------------------------*/

#endif /* HTTP */