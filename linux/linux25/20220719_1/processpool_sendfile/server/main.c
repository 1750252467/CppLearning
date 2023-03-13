 ///
 /// @file    main.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 14:36:14
 ///
 
#include "process_pool.h"
#include "tcp.h"
 
int main(int argc, char *argv[])
{
	//ip,port,processNum
	ARGS_CHECK(argc, 4);
	int processNumber = atoi(argv[3]);
	pProcess_data_t pProcessData = (pProcess_data_t)calloc(processNumber, sizeof(process_data_t));
	//1. 创建N个子进程
	makeChild(processNumber, pProcessData);

	//2. 监听新客户端的到来
	int listenfd = tcpInit(argv[1], atoi(argv[2]));
	
	//3. 创建epoll的实例
	int epfd = epoll_create1(0);
	ERROR_CHECK(epfd, -1, "epoll_create1");

	//4.1 监听listenfd
	epollAddReadEvent(epfd, listenfd);
	for(int i = 0; i < processNumber; ++i) {
		//4.2 监听父进程与子进程通信的管道
		epollAddReadEvent(epfd, pProcessData[i].pipefd);
	}

	struct epoll_event * pevtList = (struct epoll_event*)
		calloc(MAXCONNS, sizeof(struct epoll_event));

	//5. 事件循环
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
					int peerfd = accept(listenfd, NULL, NULL);
					ERROR_CHECK(peerfd, -1, "accept");
					//将peerfd交给一个空闲的子进程
					for(int j = 0; j < processNumber; ++j) {
						if(pProcessData[j].busy == FREE) {
							sendFd(pProcessData[j].pipefd, peerfd);
							pProcessData[j].busy = BUSY;//设置子进程处于忙碌状态
							break;
						}
					}
					close(peerfd);//在父进程中关闭peerfd
				} else {
				//2. 管道可读: 子进程给父进程发了通知
					int howmany = 0;
					read(fd, &howmany, sizeof(howmany));
					//设置子进程处于空闲状态
					for(int j = 0; j < processNumber; ++j) {
						if(pProcessData[j].pipefd == fd) {
							pProcessData[j].busy = FREE;
							printf(">> child %d is not busy.\n", pProcessData[j].pid);
							break;
						}
					}
				}
			}
		}
	}

	free(pevtList);
	close(listenfd);
	close(epfd);
	return 0;
}

