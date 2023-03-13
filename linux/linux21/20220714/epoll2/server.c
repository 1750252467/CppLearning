 ///
 /// @file    server.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-12 11:40:07
 ///
 
#include "tcp.h"

#define MAXCONNS 2000


//当你写函数时，如果发现超过50行，要考虑进行封装了
 
int main(int argc, char *argv[])
{
	int listenfd = tcpInit("127.0.0.1", 8899);
//	setNonBlock(listenfd);//将listenfd设置成非阻塞
	//1. 创建epoll的实例
	int epfd = epoll_create1(0);
	ERROR_CHECK(epfd, -1, "epoll_create1");
	
	//2. 对listenfd进行监听
	epollAddReadEvent(epfd, listenfd);
	int ret = -1;
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
					ret = handleNewConnection(epfd, listenfd);
				} else {
					//2.处理已经建立好的连接
					ret = handleMessage(epfd, fd);
				}
			}
		}
	}
	close(listenfd);
	return 0;
}
