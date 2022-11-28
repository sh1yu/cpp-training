//
// Created by psy on 2022/6/12.
//

#ifndef C_HTTP_SERVER_HANDLER_H
#define C_HTTP_SERVER_HANDLER_H

#include <event2/event.h>
#include <event2/http.h> //http
#include <event2/buffer.h>
#include <event2/http_struct.h>
#include <event2/keyvalq_struct.h>

#define MYMETHOD_SIGNATURE "my httpd v 0.0.1"

void http_handler(struct evhttp_request *request, void *arg);

#endif C_HTTP_SERVER_HANDLER_H
