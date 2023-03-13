#include <func.h>

int main(int argc,char*argv[]){
    //创建套结字
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(listenfd,-1,"socket");

    //设置服务器的网络地址
    printf("sizeof(struct sockaddr):%ld\n",sizeof(struct sockaddr));
    printf("sizeof(struct sockaddr_in):%ld\n",sizeof(struct sockaddr_in));

    //1.设置服务器的网络地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr,0,sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port  = htons(8888);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.128.129");

    int ret = bind(listenfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"bind");

    ret = listen(listenfd,100);
    ERROR_CHECK(ret ,-1,"listen");
    while(1);
    return 0;
}
