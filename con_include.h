#ifndef CON_INCLUDE_H
#define CON_INCLUDE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <iostream>

#define DEFAULT_AVR_PORT  8181
#define FILE_MAX_LEN  64

#endif //CON_INCLUDE_H