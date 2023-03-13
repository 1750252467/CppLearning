#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#define ARGS_CHECK(argc,val) {if(argc!=val) \
    {printf("error args\n"); return -1;}}

#define ERROR_CHECK(ret,retVal,funcName) {if(ret==retVal) {perror(funcName);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName)  do{\
	if(0 != ret) {\
	printf("%s: %s\n", funcName, strerror(ret));\
	}\
}while(0)

#define CHILD_THREAD_ERROR_CHECK(ret,funcName)  do{  if(0 != ret) {  printf("%s : %s \n",funcName,strerror(ret)); return (void*)-1;   }   }while(0)
#define FREE 0
#define BUSY 1

typedef struct process_data
{
	pid_t pid;//子进程的pid
	int pipefd;//父进程与子进程通信的管道
	short busy;//0 空闲;  1 忙碌
} process_data_t, *pProcess_data_t;

void makeChild(int processNumber, pProcess_data_t pProcessData);
void childHandleTask(int pipefd);
int sendFd(int pipefd, int fd);
int recvFd(int pipefd, int * childfd);
