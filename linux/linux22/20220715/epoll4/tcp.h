 ///
 /// @file    tcp.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-14 16:08:52
 ///
 
#ifndef __WD_TCP_H__
#define __WD_TCP_H__
#include <head.h>

#define BUFFSIZE 1000
#define MAXCONNS 1000

typedef struct channel_s {
	int sockfd;
	int recvBuffSize;//接收缓冲区中的数据长度
	char recvBuff[BUFFSIZE];
	int sendBuffSize;//发送缓冲区中的数据长度
	char sendBuff[BUFFSIZE];
}channel_t;

//对某一个通道进行初始化
void channelInit(channel_t * pconn);
//在通道数组中添加一个通道
void channelAdd(channel_t * pconns, int fd);
//从通道数组中删除一个通道
void channelDel(channel_t * pconns, int fd);
//获取该fd在通道数组中的下标
int channelGetIndex(channel_t * pconns, int fd);

//清空接收缓冲区
void channelClearRecvBuff(channel_t * pconn);
//清空发送缓冲区
void channelClearSendBuff(channel_t * pconn);



int tcpInit(const char * ip, unsigned short port);
void setNonBlock(int fd);

int epollAddReadEvent(int epfd, int fd);//添加读事件的监听
int epollAddReadWriteEvent(int epfd, int fd);//添加读写事件的监听
int epollDelEvent(int epfd, int fd);//删除某一个fd的监听
int epollClearWriteEvent(int epfd, int fd);//清除写事件
int epollSetWriteEvent(int epfd, int fd);//设置写事件
	
int eventloop(int epfd, int listenfd, 
		struct epoll_event *pevtList, int size);

int handleNewConnection(int epfd, int listenfd, channel_t * pconns);
int handleReadEvent(int epfd, int fd, channel_t * pconns);
int handleWriteEvent(int epfd, int fd, channel_t * pconns);
 
#endif
