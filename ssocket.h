#ifndef S_SOCKET_H
#define S_SOCKET_H

#include "con_include.h"

namespace ssocket{
    static void setReusePort(int);  //设置端口监听的TIME_WAIT复用
    class ClientSocket;   
    class ServerSocket{
        public: 
            ServerSocket(int port = DEFAULT_AVR_PORT,const char* ip= nullptr);
            ~ServerSocket();//构造函数
            //bind
            void socket_bind();
            //listen
            void socket_listen();
            //accpet
            int socket_accpet(ClientSocket &);
            //信号处理函数--->让服务器按下ctrl+c时不会退出 -->未实现
            //void signahandler(void);

        public:
            struct sockaddr_in m_Addr;
            int sock_fd;
            int m_Port;
            const char* m_Ip;
    };
    class ClientSocket{
        public:
            ~ClientSocket();

        public:
            struct sockaddr_in m_Addr;
            socklen_t m_Len;
            int fd;
    };

}//namespace ssocket

#endif //S_SOCKET_H