#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include "tcp.h"
#include "taskqueue.h"

#include <func.h>

#define SENDBUFFSIZE 1000
//#define BUFFSIZE 1000

typedef struct {
	pthread_t * threads;
	int threadNumber;
	task_queue_t queue;
} thread_pool_t, *pThread_pool_t;

typedef struct {
	int length;
	char buff[BUFFSIZE];
} train_t;

void * threadFunc(void*);

void threadpoolInit(thread_pool_t*, int);
void threadpoolDestroy(thread_pool_t*);
void threadpoolStart(thread_pool_t * pthreadpool);
 
int transferfile(int peerfd, const char * filename);
 
 
#endif
