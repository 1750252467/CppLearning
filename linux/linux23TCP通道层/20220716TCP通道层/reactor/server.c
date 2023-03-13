 ///
 /// @file    server.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-12 11:40:07
 ///
 
#include "tcp.h"
#define EVENTSIZE 2000


//当你写函数时，如果发现超过50行，要考虑进行封装了

void onConnection(int sockfd);
void onMessage(int sockfd, channel_t * pconns);
void onClose(int sockfd);
 
int main(int argc, char *argv[])
{
	int listenfd = tcpInit("127.0.0.1", 8888);
	//setNonBlock(listenfd);//将listenfd设置成非阻塞
	//1. 创建epoll的实例
	int epfd = epoll_create1(0);
	ERROR_CHECK(epfd, -1, "epoll_create1");
	//2. 对listenfd进行监听
	epollAddReadEvent(epfd, listenfd);
	struct epoll_event *pevtList =(struct epoll_event*)calloc(EVENTSIZE, sizeof(struct epoll_event));
	//3. 事件循环
	eventloop(epfd, listenfd, pevtList, EVENTSIZE,
			onConnection, onMessage, onClose);
	//4. 回收资源
	close(listenfd);
	close(epfd);
	free(pevtList);
	return 0;
}

//可以根据自己的需要随便扩展，
//而不需要修改原来的代码
void onConnection(int sockfd)
{
	//当连接建立好的时候，希望进行一个记录,记录四元组信息
	printf(">>> conn %s:%d ---> %s:%d has connected!\n",
			getLocalIp(sockfd), getLocalPort(sockfd),
			getPeerIp(sockfd), getPeerPort(sockfd));
}

void onMessage(int sockfd, channel_t * pconns)
{
	int idx = channelGetIndex(pconns, sockfd);
	if(idx < 0) {
		return ;
	}
	//recv-decode-compute-encode

	//1. 接收数据,放入接收缓存区
	int ret = recv(sockfd, pconns[idx].recvBuff, BUFFSIZE, 0);
	printf("recv from client:%d, %s\n", ret, pconns[idx].recvBuff);
	pconns[idx].recvBuffSize = ret;//更新接收缓冲区大小
	
	//2. 在这里并不真正去做发送操作,而是将数据放入发送缓冲区中
	strncpy(pconns[idx].sendBuff + pconns[idx].sendBuffSize, 
			pconns[idx].recvBuff, ret);
	pconns[idx].sendBuffSize += ret;//更新发送缓冲区的长度

	//3.接收到的数据已经处理完毕，清空接收缓冲区
	channelClearRecvBuff(&pconns[idx]);
}

void onClose(int sockfd) {
	//连接断开时, 也需要做一个记录
	printf(">> conn %s:%d --> %s:%d has closed!\n",
			getLocalIp(sockfd), getLocalPort(sockfd),
			getPeerIp(sockfd), getPeerPort(sockfd));
}
