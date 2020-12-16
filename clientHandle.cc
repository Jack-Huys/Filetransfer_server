#include "clientHandle.h"
void f_time(){

    time_t  time1;
    struct tm *t;//年月日时分秒的结构体定义一个结构体指针,localtime里面自有的
    time(&time1);//获取到1900年的秒数
    //time_t time(time_t *tloc);
    // struct tm *localtime(const time_t *timep);
    t = localtime( &time1);//获取当前时间
    printf("%d-%d-%d  %d:%d:%d\n", t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
}
void * handle_client(void * argc){
    
    char filename[FILE_MAX_LEN+1];
    int *m_sock;
    char buffer[MAX_SIZE]{0};
    int m_len;
    //m_sock = static_cast<int>(argc);
    m_sock = (int *)argc;
    std::cout <<"//////////begin send////////"<<std::endl;
    FILE * file = fopen(filename,"r");
    if(file == NULL){
        close(*m_sock);
        exit;
    }
    //发送文件名
    int ret = send(*m_sock, filename, FILE_MAX_LEN, 0);
    if(ret == -1){
        perror("send:\n");
        goto EXIT_THREAD;
    }
    std::cout<<"begin send file "<<filename<<"....."<<std::endl;

    //发送文件内容
    while(!feof(file)){
        m_len = fread(buffer, 1, sizeof(buffer), file);
        std::cout << "server read from"<<filename<<",len = "<<m_len<<std::endl;

        if (send(*m_sock, buffer, m_len, 0)<0)
        {
            perror("send:\n");
            goto EXIT_THREAD;
        }       
    }
    //跳转语句
    EXIT_THREAD:
        if(file){
            fclose(file);
            close(*m_sock);
        }
}