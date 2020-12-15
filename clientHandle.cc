#include "clientHandle.h"
void * Handle::handle_client(void * argc){
    //sock = static_cast<int>(argc);
    m_sock = (int)argc;
    std::cout <<"//////////begin send////////"<<std::endl;
    FILE * file = fopen(filename,"r");
    if(file == NULL){
        close(m_sock);
        exit;
    }
    //发送文件名
    int ret = send(m_sock, filename, FILE_MAX_LEN, 0);
    if(ret == -1){
        perror("send:\n");
        goto EXIT_THREAD;
    }
    std::cout<<"begin send file "<<filename<<"....."<<std::endl;

    //发送文件内容
    while(!feof(file)){
        m_len = fread(buffer, 1, sizeof(buffer), file);
        std::cout << "server read from"<<filename<<",len = "<<m_len<<std::endl;

        if (send(m_sock, buffer, m_len, 0)<0)
        {
            perror("send:\n");
            goto EXIT_THREAD;
        }       
    }
    //跳转语句
    EXIT_THREAD:
        if(file){
            fclose(file);
            close(m_sock);
        }
}