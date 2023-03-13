
#include "process_pool.h"
#include "tcp.h"

int exitPipe[2];

void sigfunc(int signum)
{
	printf(">> sigfunc\n");
	char ch = 1;
	write(exitPipe[1], &ch, 1);
}

 
int main(int argc, char *argv[])
{   //server端先忽略掉该信号
	signal(SIGPIPE, SIG_IGN);

	//输入ip,port,processNum
	ARGS_CHECK(argc, 4);
    //输入创建的子进程个数processNum,atoi将字符串转化为int
    //初始化通信通道
	int processNumber = atoi(argv[3]);
	pProcess_data_t pProcessData = (pProcess_data_t)calloc(processNumber, sizeof(process_data_t));
	//1. 创建N个子进程
	makeChild(processNumber, pProcessData);

	//只作用于父进程，不作用于子进程
	//因此要放在子进程创建结束之后
	pipe(exitPipe);
	signal(SIGUSR1, sigfunc);

	//2. 监听新客户端的到来
    //输入argv1，argv2,ip and 网络端口号
	int listenfd = tcpInit(argv[1], atoi(argv[2]));
	
	//3. 创建epoll的实例
	int epfd = epoll_create1(0);
	ERROR_CHECK(epfd, -1, "epoll_create1");

	//4.1 监听listenfd
	epollAddReadEvent(epfd, listenfd);
	epollAddReadEvent(epfd, exitPipe[0]);//监听进程池退出的管道
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
							sendFd(pProcessData[j].pipefd, peerfd, PROCESSPOOL_NOT_EXIT_FLAG);
							pProcessData[j].busy = BUSY;//设置子进程处于忙碌状态
							break;
						}
					}
					close(peerfd);//在父进程中关闭peerfd
				} else if(fd == exitPipe[0]) {
					//进程池退出的操作
					char ch;
					read(exitPipe[0], &ch, 1);
					for(int j = 0; j < processNumber; ++j) {
						printf("notify child %d exit\n", pProcessData[j].pid);
						sendFd(pProcessData[j].pipefd, 0, PROCESSPOOL_EXIT_FLAG);
					}

					for(int j = 0; j < processNumber; ++j) {
						wait(NULL);//父进程回收子进程的资源
					}
					printf("parent process exit!\n");
					exit(0);
				} 
				else {
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

