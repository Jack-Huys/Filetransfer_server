#include "ssocket.h"
#include "clientHandle.h"
#include "con_include.h"

using namespace std;

int main(){
    pthread_t thread_t;
    int new_fd;
    ssocket::ServerSocket server;
    ssocket::ClientSocket clientSocket;
    server.socket_bind();
    server.socket_listen();
    
    while(true){
        int sin_size = sizeof(struct sockaddr_in);

        if(new_fd = server.socket_accpet(clientSocket) == -1){
            perror("accpet");
            goto EXIT_MAIN;
        }
        printf("///// client(ip=%s:port=%d requst /////\n", 
                inet_ntoa(clientSocket.m_Addr.sin_addr), ntohs(clientSocket.m_Addr.sin_port));

        //生成一个线程来完成和客户端的会话，父进程继续监听
        int ret=pthread_create(&thread_t, NULL, handle_client, (void *)&new_fd);
        if(ret){
            cout << "creat pthread fail" <<endl;
            return -1;
        }
    }

    EXIT_MAIN:
    close(server.sock_fd);
    return 0;
}