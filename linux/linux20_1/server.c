#include <func.h>

#define MAXCONNS 1000

int main(int argc,char *argv[]){
    //创建套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    printf("listentfd: %d\n",listenfd);
    ERROR_CHECK(listenfd,-1,"socket");

    printf("sizeof(struct sockaddr):%ld\n",sizeof(struct sockaddr));
    printf("sizeof(struct sockaddr_in):%ld\n",sizeof(struct sockaddr_in));

    //将网络地址设置为可以重用
    int on = 1;
    int ret = setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    ERROR_CHECK(ret,-1,"setsockopt");

    //1.设置服务器的网络地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr,0,sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;//IPV4
    serverAddr.sin_port = htons(8899);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.128.129");

    ret = bind(listenfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"bind");

    ret = listen(listenfd,100);
    ERROR_CHECK(ret,-1,"listen");

    //设置文件描述符
    fd_set rdset;
    int maxfd = listenfd;
    int connfds[MAXCONNS] = {0};

    //打印当前本地时间

    time_t now;              
    now = time(NULL);
    printf("%s",ctime(&now));
    while(1){
        //每一次select调用之前都需要监听相应文件描述符
        FD_ZERO(&rdset);
        FD_SET(listenfd,&rdset);//将listenfd加入监听
        //遍历整个数组，将所有已经建立好的连接加入到select中进行监听
        for(int i=0;i < MAXCONNS;i++){
            if(connfds[i]!=0){
                FD_SET(connfds[i],&rdset);
            }
        }


        //当select调用完成时，已经就绪的fd也写入到了rdset中
       // printf("before select\n");
        int nready = select(maxfd+1,&rdset,NULL,NULL,NULL);
       // printf("after select nready:%d\n",rdset);

        if(FD_ISSET(listenfd,&rdset)){
            //1,进行连接的处理
            int peerfd = accept(listenfd,NULL,NULL);
            ERROR_CHECK(peerfd,-1,"accept");
            //保存已经建立好的连接
            for(int i = 0;i < MAXCONNS;++i){
                if(connfds[i] == 0){
                    connfds[i] = peerfd;
                    break;
                }
            }
            //更新maxfd
            if(maxfd<peerfd){
                maxfd = peerfd;
            }
        }
        for(int i= 0;i< MAXCONNS; ++i){
            if(connfds[i] != 0){
                //处理已经建立好的连接
                if(FD_ISSET(connfds[i],&rdset)){
                    //表示对端有数据过来，执行读操作
                    char recvbuff[100] = {0};
                    //接收数据
                    ret = read(connfds[i],recvbuff,sizeof(recvbuff));
                    if(ret > 0){
                        printf("recv from client:%d,%s",ret,recvbuff);
                        //执行回显操作
                      //  printf(">>%d send %ld bytes data\n",connfds[i],strlen(recvbuff)-1);
                        //打印当前本地时间
                        time_t now;     
                        now = time(NULL);
                        printf("%s\n",ctime(&now));
                
                        scanf("%s",recvbuff);
                        ret=write(connfds[i],recvbuff,strlen(recvbuff));
                   ERROR_CHECK(ret,-1,"write");
                    }else if(ret == 0){

                        time_t now;              
                        now = time(NULL);
                        printf("%s",ctime(&now));
                        printf("coon has closed\n");
                        close(connfds[i]);
                        connfds[i] = 0;//将该fd从分组中清除掉 
                    }else if(ret<0){
                        perror("recv");
                    }
                }
            }
        }
    }
    close(listenfd);
    return 0;
}
