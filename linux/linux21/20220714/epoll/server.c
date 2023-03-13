 ///
 /// @file    server.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-12 11:40:07
 ///
 
#include <head.h>

#define MAXCONNS 2000
 
int main(int argc, char *argv[])
{
	//0. 创建套接字
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("lisentfd: %d\n", listenfd);
	ERROR_CHECK(listenfd, -1, "socket");

	printf("sizeof(struct sockaddr):%ld\n", sizeof(struct sockaddr));
	printf("sizeof(struct sockaddr_in):%ld\n", sizeof(struct sockaddr_in));

	//将网络地址设置为可以重用的
	int on = 1;
	int ret = setsockopt(listenfd, SOL_SOCKET, 
			SO_REUSEADDR, 
			&on, sizeof(on));
	ERROR_CHECK(ret, -1, "setsockopt");

	//1. 设置服务器的网络地址
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8899);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.30.128");

	ret = bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	ERROR_CHECK(ret, -1, "bind");

	ret = listen(listenfd, 100);
	ERROR_CHECK(ret, -1, "listen");

	//1. 创建epoll的实例
	int epfd = epoll_create1(0);
	ERROR_CHECK(epfd, -1, "epoll_create1");

	//2. 对listenfd进行监听
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;  //监听读事件
	ev.data.fd = listenfd;//对listenfd进行监听
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
	ERROR_CHECK(ret, -1, "epoll_ctl");

	struct epoll_event *pevtList = calloc(MAXCONNS, sizeof(struct epoll_event));

	//事件循环
	while(1) {
		printf("before epoll_wait\n");
		//当epoll_wait返回时，前nready已经就绪的fd信息写入到了pevtList数组的
		//前nready个位置上
		int nready = epoll_wait(epfd, pevtList, MAXCONNS, -1);
		printf("after epoll_wait nready: %d\n", nready);

		if(nready == -1 && errno == EINTR) {
			continue;
		} else if(0 == nready) {
			//epoll_wait超时
			printf(">> epoll timeout\n");
		} else if(-1 == nready){
			perror("epoll_wait");
			return EXIT_FAILURE;
		} else {
			//nready > 0 的情况
			for(int i = 0; i < nready; ++i) {
				int fd = pevtList[i].data.fd;
				//1. 进行新连接的处理
				if(fd == listenfd) {
					int peerfd = accept(listenfd, NULL, NULL);
					ERROR_CHECK(peerfd, -1, "accept");
					//对新连接的读事件进行监听(只需要监听一次)
					struct epoll_event ev;
					memset(&ev, 0, sizeof(ev));
					ev.events = EPOLLIN;
					ev.data.fd = peerfd;
					ret = epoll_ctl(epfd, EPOLL_CTL_ADD, peerfd, &ev);
					ERROR_CHECK(ret, -1, "epoll_ctl");
				} else {
					//只有不是listenfd，那就一定是已经建立好的连接
					//2.处理已经建立好的连接
					//表示对端有数据过来,执行读操作
					char recvbuff[100] = {0};
					//接收数据, 默认情况下recv是阻塞式函数
					//当第四个参数设置为MSG_WAITALL时，必须要接收指定的字节数才能返回
					//当第四个参数设置为MSG_DONTWAIT时，就是非阻塞的
					ret = recv(fd, recvbuff, sizeof(recvbuff), MSG_DONTWAIT);
					if(ret > 0) {
						printf("recv from client:%d, %s\n", ret, recvbuff);
						//执行回显操作
						ret = send(fd, recvbuff, strlen(recvbuff), 0);
						printf(">> %d send %d bytes data\n", fd, ret);
					} else if(0 == ret) {
						printf("conn has closed\n");
						//连接断开后，还要将其从监听的红黑树上删除掉
						struct epoll_event ev;
						ev.data.fd = fd;
						ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
						ERROR_CHECK(ret, -1, "epoll_ctl");
						close(fd);
					} else if(ret < 0){
						perror("recv");
					}

					ret = recv(fd, recvbuff, sizeof(recvbuff), 0);
					printf("2nd ret: %d\n", ret);
					perror("recv");

				}
			}
		}
	}
	close(listenfd);
	return 0;
}
