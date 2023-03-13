#include "func.h"
#define _GNU_SOURCE
#define CHILD_THREAD_ERROR_CHECK(ret,funcName)  do{  if(0 != ret) {  printf("%s : %s \n",funcName,strerror(ret)); return (void*)-1;   }   }while(0)
#define FREE 0
#define BUSY 1
#define BUFFSIZE 1000
#define PROCESSPOOL_EXIT_FLAG 1
#define PROCESSPOOL_NOT_EXIT_FLAG 0

typedef struct train_s
{
	int length;//数据的长度
	char buff[BUFFSIZE];//存放数据
}train_t;

typedef struct process_data
{
	pid_t pid;//子进程的pid
	int pipefd;//父进程与子进程通信的管道
	short busy;//0 空闲;  1 忙碌
} process_data_t, *pProcess_data_t;

void makeChild(int processNumber, pProcess_data_t pProcessData);
void childHandleTask(int pipefd);
int sendFd(int pipefd, int fd, char exitflag);
int recvFd(int pipefd, int * childfd, char * pexitflag);
int transferfile(int peerfd);
