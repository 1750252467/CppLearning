 ///
 /// @file    child.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 14:40:49
 ///
 
#include "process_pool.h"
 
void makeChild(int processNumber, pProcess_data_t pProcessData)
{
	for(int i = 0; i < processNumber; ++i) {
		int fds[2];
		socketpair(AF_LOCAL, SOL_SOCKET, 0, fds);
		int pid = fork();
		if(0 == pid) {
			close(fds[1]);
			//子进程要做的事儿就是执行任务
			childHandleTask(fds[0]);
			exit(0);
		}

		close(fds[0]);
		//父进程部分
		pProcessData[i].pid = pid;
		pProcessData[i].pipefd = fds[1];
		pProcessData[i].busy = FREE;
	}
}

void childHandleTask(int pipefd)
{
	printf("child is running\n");
	while(1)
	{
		int childfd;
		//1. 没有任务时，阻塞在recvFd之上
		//一旦recvFd返回，就表示有任务到达
		recvFd(pipefd, &childfd);

		//2. 发送文件
		//send(childfd, "hello,wuhan", 11, 0);
		transferfile(childfd);

		//3. 如果发送完成，那就关闭该连接
		close(childfd);

		//4. 通知父进程(往管道上写点儿数据)
		int one = 1;
		write(pipefd, &one, sizeof(one));
	}
}
