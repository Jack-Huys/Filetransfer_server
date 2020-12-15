#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#include "con_include.h"

class Handle{
    public:
        void * handle_client(void * argc);
        void f_time();

    public:
        char filename[FILE_MAX_LEN+1];
        int m_sock;
        char buffer[MAX_SIZE]{0};
        int m_len;

    
};

#endif //CLIENT_HANDLE_H