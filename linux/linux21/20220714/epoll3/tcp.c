 
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
	ev.events = EPOLLIN | EPOLLET;  //监听读事件
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

int eventloop(int epfd, int listenfd, struct epoll_event *pevtList, int size)
{
	int ret = -1;
	while(1) {
		printf("before epoll_wait\n");
		//当epoll_wait返回时，前nready已经就绪的fd信息写入到了pevtList数组的
		//前nready个位置上
		int nready = epoll_wait(epfd, pevtList, size, -1);
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
	return 0;
}

int handleNewConnection(int epfd, int listenfd) {
	int peerfd = accept(listenfd, NULL, NULL);
	ERROR_CHECK(peerfd, -1, "accept");
	//对新连接的读事件进行监听(只需要监听一次)
	epollAddReadEvent(epfd, peerfd);
	//将peerfd套接字其设置为非阻塞
	setNonBlock(peerfd);
	return 0;
}

int handleMessage(int epfd, int fd)
{
	//表示对端有数据过来,执行读操作
	char recvbuff[100] = {0};
	//接收数据, 此时recv是非阻塞式函数

	printf("handleMessage ....\n");
#if 1
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
#endif
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
