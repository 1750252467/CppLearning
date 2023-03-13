 ///
 /// @file    tcp.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-14 16:10:34
 ///
 
#include "tcp.h" 


void channelInit(channel_t * pconn)
{
	pconn->recvBuffSize = 0;
	pconn->sendBuffSize = 0;
	memset(pconn->recvBuff, 0, BUFFSIZE);
	memset(pconn->sendBuff, 0, BUFFSIZE);
}
void channelAdd(channel_t * pconns, int fd)
{
	for(int i = 0; i < MAXCONNS; ++i) {
		if(pconns[i].sockfd == 0) {
			pconns[i].sockfd = fd;
			channelInit(&pconns[i]);
			break;
		}
	}
}

void channelDel(channel_t * pconns, int fd)
{
	int idx = channelGetIndex(pconns, fd);
	if(idx >= 0) {
		pconns[idx].sockfd = 0;
		channelInit(&pconns[idx]);
	}
}

int channelGetIndex(channel_t * pconns, int fd)
{
	for(int i = 0; i < MAXCONNS; ++i) {
		if(pconns[i].sockfd == fd) {
			return i;//找到了
		}
	}
	return -1;// 未找到
}

void channelClearRecvBuff(channel_t * pconn)
{
	if(pconn) {
		pconn->recvBuffSize = 0;
		memset(pconn->recvBuff, 0, BUFFSIZE);
	}
}

void channelClearSendBuff(channel_t * pconn)
{
	if(pconn) {
		pconn->sendBuffSize = 0;
		memset(pconn->sendBuff, 0, BUFFSIZE);
	}
}
 
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

int eventloop(int epfd, int listenfd, 
		struct epoll_event *pevtList, int size,
		EventCallback onConnectionCb,
		EventMessageCallback onMessageCb,
		EventCallback onCloseCb)
{
	channel_t * pconns = (channel_t*)calloc(MAXCONNS, sizeof(channel_t));
	int ret = -1;
	while(1) {
		printf("before epoll_wait\n");
		//当epoll_wait返回时，前nready已经就绪的fd信息写入到了pevtList数组的
		//前nready个位置上
		int nready = epoll_wait(epfd, pevtList, size, 5000);
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
					ret = handleNewConnection(epfd, listenfd, pconns, onConnectionCb);
				} else {
					//2.处理已经建立好的连接
					//2.1 针对于读事件的处理
					if(pevtList[i].events & EPOLLIN) {
						ret = handleReadEvent(epfd, fd, pconns, onMessageCb, onCloseCb);
					}
					//2.2 针对于写事件的处理
					if(pevtList[i].events & EPOLLOUT) {
						printf(">> write event trigger\n");
						ret = handleWriteEvent(epfd, fd, pconns);
					}
				}
			}
		}
	}
	free(pconns);
	return 0;
}

int handleNewConnection(int epfd, 
	int listenfd, 
	channel_t * pconns,
	EventCallback onConnectionCallback) 
{
	int peerfd = accept(listenfd, NULL, NULL);
	ERROR_CHECK(peerfd, -1, "accept");
	channelAdd(pconns, peerfd);//将peerfd添加到了通道数组中
	//对新连接的读事件进行监听(只需要监听一次)
	epollAddReadWriteEvent(epfd, peerfd);
	//将peerfd套接字其设置为非阻塞
	setNonBlock(peerfd);

	//连接建立时的事件处理器[扩展点]
	onConnectionCallback(peerfd);
	return 0;
}

int handleReadEvent(int epfd, int fd, channel_t * pconns, 
		EventMessageCallback onMessageCallback, 
		EventCallback onCloseCallback)
{
	printf("handleReadEvent...\n");
	//1. 先判断该连接是否断开
	char recvbuff[20] = {0};
	int ret = recv(fd, recvbuff, sizeof(recvbuff), MSG_PEEK);
	if(ret > 0) {
		//2. 消息到达时的事件处理器[扩展点]
		onMessageCallback(fd, pconns);

		//3. 当发送缓冲区长度值大于0时，表示有数据要进行发送
		int idx = channelGetIndex(pconns, fd);
		if(idx >= 0 && pconns[idx].sendBuffSize > 0) {
			epollSetWriteEvent(epfd, fd);//触发写事件
		}
	} else if(0 == ret) {
		//4. 连接断开时的事件处理器[扩展点]
		onCloseCallback(fd);
		epollDelEvent(epfd, fd);//从epoll的监听中删除
		channelDel(pconns, fd);//从通道数组中删除该通道
		close(fd);//关闭套接字
	} else if(ret < 0){
		perror("recv");
	}
	return 0;
}

int handleWriteEvent(int epfd, int fd, channel_t * pconns)
{
	int idx = channelGetIndex(pconns, fd);
	int ret = -1;
	//1. 当发现发送缓冲区没有数据时，就清除写事件的监听
	if(pconns[idx].sendBuffSize == 0) {
		epollClearWriteEvent(epfd, fd);
	} else {
		//2. 当发送缓冲区有数据时，进行数据的发送操作
		ret = send(fd, pconns[idx].sendBuff, pconns[idx].sendBuffSize, 0);
		if(ret >= 0) {
			//3. 更新发送缓存去中的数据长度
			pconns[idx].sendBuffSize -= ret;
			//4. 如果数据全部发送完毕，就清除写事件的监听
			if(pconns[idx].sendBuffSize == 0) {
				epollClearWriteEvent(epfd, fd);
			} else {
			//5.发送缓冲区中还有部分数据没有发送完成，
			//因此需要进行滑动窗口机制，移走已经发送的数据
			//等待下一次的epoll_wait返回时，再进行发送
				memmove(pconns[idx].sendBuff, 
						pconns[idx].sendBuff + ret, 
						pconns[idx].sendBuffSize);
			}
		} else {
			perror("send");
			return EXIT_FAILURE;
		}
	}
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
	if(getsockname(sockfd, (struct sockaddr*)&addr, &len) < 0) {
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
