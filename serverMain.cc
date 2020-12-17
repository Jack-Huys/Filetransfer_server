#include "ssocket.h"
#include "con_include.h"

using namespace std;
static char filename[FILE_MAX_LEN+1];

void f_time(){

    time_t  time1;
    struct tm *t;//年月日时分秒的结构体定义一个结构体指针,localtime里面自有的
    time(&time1);//获取到1900年的秒数
    //time_t time(time_t *tloc);
    // struct tm *localtime(const time_t *timep);
    t = localtime( &time1);//获取当前时间
    printf("%d-%d-%d  %d:%d:%d\n", t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
}
static void * handle_client(void * argc){
    f_time();
    //char filename[FILE_MAX_LEN+1];
    int *m_sock;
    char buffer[MAX_SIZE]{0};
    int m_len;
    //m_sock = static_cast<int>(argc);
    m_sock = (int*)argc;
    std::cout <<"//////////begin send////////"<<std::endl;
    FILE * file = fopen(filename,"r");
    if(file == NULL){
        close(*m_sock);
        exit;
    }
    //发送文件名
    cout <<"filename:"<<filename<<endl;
    int ret = send(*m_sock, filename, FILE_MAX_LEN, 0);
    if(ret == -1){
        perror("send:");
        exit(-1);
        //goto EXIT_THREAD;
    }
    std::cout<<"///////begin send file "<<filename<<"...../////////"<<std::endl;

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
    fclose(file);
    close(*m_sock);
    
}
int main(int argc,char * argv[]){
    pthread_t thread_t;
    int new_fd;
    //char name[FILE_MAX_LEN];
    ssocket::ServerSocket server;
    ssocket::ClientSocket clientSocket;
    // if(argc <2){
    //     cout <<"need a filename without path"<<endl;
    // }
    DIR *dirp;
        struct dirent *dp;
        dirp = opendir("/home/GitHub/Filetransfer_server/"); //打开目录指针
        while ((dp = readdir(dirp)) != NULL) { //通过目录指针读目录
            printf("%s\n", dp->d_name );
        }
    closedir(dirp); //关闭目录
    cout <<"///////choice one to send//////////"<<endl;
    cin.getline(filename,FILE_MAX_LEN);
    //strncpy(filename, name,FILE_MAX_LEN);
    server.socket_bind();
    server.socket_listen();
    
    while(true){
        int sin_size = sizeof(struct sockaddr_in);

        if((new_fd = server.socket_accpet(clientSocket)) == -1){
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