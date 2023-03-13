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
	ev.data.fd = fd;//对fd进行监听
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
	ERROR_CHECK(ret, -1, "epoll_ctl");
	return 0;
}

int epollAddReadWriteEvent(int epfd, int fd)
{
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN | EPOLLOUT;  //监听读写事件
	ev.data.fd = fd;//对fd进行监听
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

int epollClearWriteEvent(int epfd, int fd)//清除写事件
{
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;  //监听读事件
	ev.data.fd = fd;//对listenfd进行监听
	int ret = epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
	ERROR_CHECK(ret, -1, "epoll_ctl");
	return 0;

}

int epollSetWriteEvent(int epfd, int fd)//设置写事件
{
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN | EPOLLOUT;  //监听读写事件
	ev.data.fd = fd;//对listenfd进行监听
	int ret = epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev);
	ERROR_CHECK(ret, -1, "epoll_ctl");
	return 0;
}

const char * getLocalIp(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&addr, 0, sizeof(addr));
	if(getsockname(sockfd,(struct sockaddr*) &addr, &len) < 0) {
		perror("getsockname");
		return NULL;
	}
	return inet_ntoa(addr.sin_addr);
}

unsigned short getLocalPort(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&addr, 0, sizeof(addr));
	if(getsockname(sockfd,(struct sockaddr*) &addr, &len) < 0) {
		perror("getsockname");
		return -1;
	}
	return ntohs(addr.sin_port);
}

const char * getPeerIp(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&addr, 0, sizeof(addr));
	if(getpeername(sockfd,(struct sockaddr*) &addr, &len) < 0) {
		perror("getsockname");
		return NULL;
	}
	return inet_ntoa(addr.sin_addr);
}

unsigned short getPeerPort(int sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);
	memset(&addr, 0, sizeof(addr));
	if(getpeername(sockfd,(struct sockaddr*) &addr, &len) < 0) {
		perror("getsockname");
		return -1;
	}
	return ntohs(addr.sin_port);
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
