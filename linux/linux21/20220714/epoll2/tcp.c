 ///
 /// @file    tcp.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-14 16:10:34
 ///
 
#include "tcp.h" 
 
void setNonBlock(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
}

int epollAddReadEvent(int epfd, int fd)
{
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;  //监听读事件
	ev.data.fd = fd;//对listenfd进行监听
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
	ERROR_CHECK(ret, -1, "epoll_ctl");
	return 0;
}

int epollDelEvent(int epfd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
	ERROR_CHECK(ret, -1, "epoll_ctl");
	return 0;
}

int handleNewConnection(int epfd, int listenfd) {
	int peerfd = accept(listenfd, NULL, NULL);
	ERROR_CHECK(peerfd, -1, "accept");
	//对新连接的读事件进行监听(只需要监听一次)
	epollAddReadEvent(epfd, peerfd);
	//将peerfd套接字其设置为非阻塞
	setNonBlock(peerfd);

	//测试accept是否为非阻塞的
	//peerfd = accept(listenfd, NULL, NULL);
	//ERROR_CHECK(peerfd, -1, "accept");

	return 0;
}

int handleMessage(int epfd, int fd)
{
	//只有不是listenfd，那就一定是已经建立好的连接
	//表示对端有数据过来,执行读操作
	char recvbuff[100] = {0};
	//接收数据, 此时recv是非阻塞式函数
	int ret = recv(fd, recvbuff, sizeof(recvbuff), 0);
	if(ret > 0) {
		printf("recv from client:%d, %s\n", ret, recvbuff);
		//执行回显操作
		ret = send(fd, recvbuff, strlen(recvbuff), 0);
		printf(">> %d send %d bytes data\n", fd, ret);
	} else if(0 == ret) {
		printf("conn has closed\n");
		//连接断开后，还要将其从监听的红黑树上删除掉
		close(fd);
		epollDelEvent(epfd, fd);
	} else if(ret < 0){
		perror("recv");
	}

	ret = recv(fd, recvbuff, sizeof(recvbuff), 0);
	printf("2nd 111 ret: %d\n", ret);
	perror("recv");
}

int tcpInit(const char * ip, unsigned short port) {
	//0. 创建套接字
	int listenfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	ERROR_CHECK(listenfd, -1, "socket");

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
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(ip);

	//2. bind
	ret = bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	ERROR_CHECK(ret, -1, "bind");

	//3. listen
	ret = listen(listenfd, 100);
	ERROR_CHECK(ret, -1, "listen");

	return listenfd;
}
