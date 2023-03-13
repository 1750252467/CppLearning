 ///
 /// @file    tcp.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-14 16:08:52
 ///
 
#ifndef __WD_TCP_H__
#define __WD_TCP_H__
#include <func.h>

int tcpInit(const char * ip, unsigned short port);
void setNonBlock(int fd);

int epollAddReadEvent(int epfd, int fd);
int epollDelEvent(int epfd, int fd);
	
int eventloop(int epfd, int listenfd, 
		struct epoll_event *pevtList, int size);

int handleNewConnection(int epfd, int listenfd);
int handleMessage(int epfd, int fd);
 
#endif
