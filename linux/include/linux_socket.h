//
// Created by valerioneri on 6/13/19.
//

#ifndef GOPHER_LINUX_SOCKET_H
#define GOPHER_LINUX_SOCKET_H

#include "definitions.h"
int linux_socket(struct Configs configs);
void * handle_request(void * args);

#endif //GOPHER_LINUX_SOCKET_H