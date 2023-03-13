#include <func.h>

int main(){

    //0.创建套接字
    int clientfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(clientfd,-1,"socket");

    printf("sizeof(struct sockaddr):%ld\n",sizeof(struct sockaddr));
    printf("sizeof(struct sockaddr_in):%ld\n",sizeof(struct sockaddr_in));

    //1.设置服务器的网络地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr,0,sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.128.129");

    int ret = connect(clientfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"connect");

    while(1);
    return 0;
}
