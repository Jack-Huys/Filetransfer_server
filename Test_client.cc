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
#include <iostream>
#include <fstream>

#define DEFAULT_AVR_PORT  8181
#define SERVER_IP   "172.17.3.232"
#define FILE_MAX_LEN  64
#define MAX_SIZE 1024
using namespace std;

int main(int argc,char * argv[]){
    char buffer[MAX_SIZE]{0};
    char filename[FILE_MAX_LEN+1]{0};
    struct sockaddr_in server_addr;
    int m_len;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){
        perror("socket:");
        exit(-1);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_AVR_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    cout <<"connect server "<<SERVER_IP<<":"
                            <<DEFAULT_AVR_PORT<<endl;
    if(connect(sock_fd, (const sockaddr *)&server_addr, 
                            sizeof(struct sockaddr)) == -1){
        perror("connect:");
        exit(-1);
    }
    //接受文件名
    int total = 0;
    while(total < FILE_MAX_LEN){
        m_len = recv(sock_fd, filename+total, FILE_MAX_LEN-total,0);
        if(m_len<=0){
            break;
        }
        total+=m_len;
    }
    // if(total != FILE_MAX_LEN){
    //     perror("failure file name");
    //     exit(-1);
    // }
    cout <<"recv filename:"<<filename<<endl;
    FILE * file = fopen(filename, "wb");
    if(file == NULL){
        perror("file create fail");
        exit(-1);
    }
    //接受数据
    cout <<"//////recv begin////////"<<endl;
    total =0;
    while(1){
        m_len = recv(sock_fd, buffer, sizeof(buffer), 0);
        if(m_len == -1){
            break;
        }
        total+=m_len;
        fwrite(buffer, 1, m_len, file);
    }
    fclose(file);
    cout <<"recv file "<<filename<<"success total = "<<total<<endl;
    close(sock_fd);
    return 0;
}
