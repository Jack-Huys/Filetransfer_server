#include "ssocket.h"


void ssocket::setReusePort(int fd){
    int on=1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&on, sizeof(on)) == -1){
        perror("set sock reuse:");
    }
}
ssocket::ServerSocket::ServerSocket(int port,const char* ip):m_Port(port),m_Ip(ip){
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        perror("socket fail:");
        std::cout <<"creat socket error in file <" << __FILE__   
                    <<" >" << "at" <<__LINE__ <<std::endl;
        exit(-1);
    }
    memset(&m_Addr, 0 , sizeof(m_Addr));//memset(&m_Addr, 0 , sizeof(struct sockaddr));
    m_Addr.sin_family = AF_INET;
    m_Addr.sin_port = htons(port);//htons转换为网络字节序
    //对IP进行判断
    if(ip != nullptr){
        ::inet_pton(AF_INET, ip , &m_Addr.sin_addr); //ip地址转换成网络字节序
    }else{
        m_Addr.sin_addr.s_addr = INADDR_ANY;
    }
    setReusePort(sock_fd);
}
//bind
void ssocket::ServerSocket::socket_bind(){
    int ret = ::bind(sock_fd, (struct sockaddr*)&m_Addr, sizeof(struct sockaddr));
    if(ret == -1){
        perror("bind");
        std::cout <<"bind error in file <" << __FILE__   
                    <<" >" << "at" <<__LINE__ <<std::endl;
        exit(-1);
    }
}
//listen
void ssocket::ServerSocket::socket_listen(){
    int ret = ::listen(sock_fd, 5);
    if(ret == -1){
        std::cout <<"listen error in file <" << __FILE__   
                    <<" >" << "at" <<__LINE__ <<std::endl;
        exit(-1);
    }
    std::cout <<"///////////server start listening.....//////////" << std::endl;
}
//接受客户端连接
int ssocket::ServerSocket::socket_accpet(ClientSocket &clientsocket){
    memset(&clientsocket.m_Addr, 0 , sizeof(struct sockaddr));
    clientsocket.m_Len = sizeof(struct sockaddr);
    int client_fd = ::accept(sock_fd, (struct sockaddr *)&clientsocket.m_Addr, &clientsocket.m_Len);
    //client_fd = ::accept(sock_fd, NULL, NULL);
    if(client_fd == -1){
        std::cout <<"accept error in file <" << __FILE__   
                    <<" >" << "at" <<__LINE__ <<std::endl;
        ::close(sock_fd);
        exit(-1);
    }
    clientsocket.fd = client_fd;
    printf("%s %d success connect...\n", 
                inet_ntoa(clientsocket.m_Addr.sin_addr), ntohs(clientsocket.m_Addr.sin_port));
    //std::cout << "/////////hava a new accept//////////"  <<std::endl;
    return client_fd;
}
//类的析构---->关闭文件描述符
ssocket::ServerSocket::~ServerSocket(){
    ::close(sock_fd);
}
ssocket::ClientSocket::~ClientSocket(){
    ::close(fd);
}

