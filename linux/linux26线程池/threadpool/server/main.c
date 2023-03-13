 
#include "threadpool.h"
#include "func.h"
int exitpipe[2];

void sigfunc(int num) 
{
	printf("sig %d is coming\n", num);
	//通过管道通知父进程退出
	char ch = 1;
	write(exitpipe[1], &ch, 1);
}
 
int main(int argc, char *argv[])
{//ip,port,processNum
	signal(SIGUSR1, sigfunc);//10号信号
	ARGS_CHECK(argc, 4);
	int threadNum = atoi(argv[3]);
	//atoi将输入的 线程个数转化为数字argv3
	pipe(exitpipe);//创建退出的管道

	pid_t pid = fork();
	if(pid > 0) {
		close(exitpipe[0]);
		wait(NULL);
		exit(0);
	}
	//子进程
	close(exitpipe[1]);
	thread_pool_t threadpool;
	threadpoolInit(&threadpool, threadNum);
	threadpoolStart(&threadpool);

	//2. 创建TCP的监听套接字listenfd
	//argv1为ip,argv2为端口号
	int listenfd = tcpInit(argv[1], atoi(argv[2]));

	//3. 创建epoll的实例, 并注册(监听)相应文件描述符上的事件
	int epfd =  epoll_create1(0);
	ERROR_CHECK(epfd, -1, "epoll_create1");
	epollAddReadEvent(epfd, listenfd);
	epollAddReadEvent(epfd, exitpipe[0]);

	struct epoll_event * pevtList = (struct epoll_event*)
		calloc(MAXCONNS, sizeof(struct epoll_event));
	
	int nready;
	while(1) {
		do {
			//4. epoll等待事件就绪
			nready = epoll_wait(epfd, pevtList, MAXCONNS, 5000);
		}while(-1 == nready && errno == EINTR);

		if(0 == nready) {
			printf(">> epoll timeout.\n");
			continue;
		} else if(-1 == nready) {
			perror("epoll_wait");
			return EXIT_FAILURE;
		} else {//nready > 0
			
			for(int i = 0; i < nready; ++i) {
				int fd = pevtList[i].data.fd;
				if(fd == listenfd) {//5. 客户端到来的处理
					int peerfd = accept(listenfd, NULL, NULL);
					if(peerfd < 0) {
						perror("accept");
					}
					printf("accept a new conn, peerfd: %d\n", peerfd);
					//让peerfd入队
					taskEnqueue(&threadpool.queue, peerfd);

				} else if(fd == exitpipe[0]) {
					char exitflag;
					read(exitpipe[0], &exitflag, 1);
					printf("parent process ready to exit.\n");
					//收到退出的通知之后，子线程要逐步退出
					queueWakeup(&threadpool.queue);
					for(int j = 0; j < threadNum; ++j) {
						pthread_join(threadpool.threads[j], NULL);
					}
					printf("parent process pool exit\n");
					threadpoolDestroy(&threadpool);
					exit(0);
				} 
			}
		}
	}

	free(pevtList); 
	close(listenfd);
	close(epfd);
	return 0;
}
