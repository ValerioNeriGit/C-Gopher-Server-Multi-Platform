//
// Created by valerioneri on 6/13/19.
//

#ifndef GOPHER_LINUX_SOCKET_H
#define GOPHER_LINUX_SOCKET_H

#include "definitions.h"


int linux_socket(struct Configs* configs);
void * handle_request(void * args);
void* handle_request_thread(void *params);
int end_server(int fd);
void close_mutex();
void start_mutex();
#endif //GOPHER_LINUX_SOCKET_H
