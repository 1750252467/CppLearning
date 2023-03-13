#include <func.h>

int main(int argc,char *argv[]){
    //创建套结字
    int clientfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(clientfd,-1,"socket");

    printf("sizeof(struct sockaddr):%ld\n",sizeof(struct sockaddr));
    printf("sizeof(struct sockaddr_in);%ld\n",sizeof(struct sockaddr_in));

    //设置服务器的网络地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0,sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8899);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.128.129");

    int ret = connect(clientfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"connect");
    printf("coon has connected\n");
    
    //设置文件描述符 
    fd_set rdset;

    while(1){
        FD_ZERO(&rdset);
        FD_SET(clientfd,&rdset);
        FD_SET(STDIN_FILENO,&rdset);

        select(clientfd+1,&rdset,NULL,NULL,NULL);

        if(FD_ISSET(STDIN_FILENO,&rdset)){
            char recvbuff[100] = {0};
            read(STDIN_FILENO,recvbuff,sizeof(recvbuff));
            write(clientfd,recvbuff,strlen(recvbuff));
        }

        if(FD_ISSET(clientfd,&rdset)){
            char recvbuff[100] = {0};
            read(clientfd,recvbuff,sizeof(recvbuff));
            printf("recv from server: %s\n",recvbuff);
        }
        
    }

    close(clientfd);
    return 0;
}
