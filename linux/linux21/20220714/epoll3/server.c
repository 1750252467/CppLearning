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
	struct epoll_event *pevtList =(struct epoll_event*)calloc(MAXCONNS, sizeof(struct epoll_event));
	//事件循环
	eventloop(epfd, listenfd, pevtList, MAXCONNS);
	close(listenfd);
	free(pevtList);
	return 0;
}
