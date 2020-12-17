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
#include <dirent.h>


#include <iostream>
#include <fstream>

#define DEFAULT_AVR_PORT  8181
#define SERVER_IP   "172.17.3.232"
#define FILE_MAX_LEN  64
#define MAX_SIZE 1024

#endif //CON_INCLUDE_H