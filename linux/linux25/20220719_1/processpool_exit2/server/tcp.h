#ifndef __WD_TCP_H__
#define __WD_TCP_H__
#include <func.h>

#define BUFFSIZE 1000
#define MAXCONNS 10


int tcpInit(const char * ip, unsigned short port);

const char * getLocalIp(int sockfd);
unsigned short getLocalPort(int sockfd);
const char * getPeerIp(int sockfd);
unsigned short getPeerPort(int sockfd);

void setNonBlock(int fd);

int epollAddReadEvent(int epfd, int fd);//添加读事件的监听
int epollAddReadWriteEvent(int epfd, int fd);//添加读写事件的监听
int epollDelEvent(int epfd, int fd);//删除某一个fd的监听
int epollClearWriteEvent(int epfd, int fd);//清除写事件
int epollSetWriteEvent(int epfd, int fd);//设置写事件
 
#endif
