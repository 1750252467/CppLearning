
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include <pthread.h>

#define TASKQUEUE_NOT_EXIT_FLAG 0
#define TASKQUEUE_READY_EXIT_FLAG 1

typedef struct task_s{
	int peerfd;
	struct task_s * pnext;
} task_t;

typedef struct taskqueue_s{
	task_t * pFront;
	task_t * pRear;
	int queSize;
	int exitFlag;//退出的标志位
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} task_queue_t;
 
void queueInit(task_queue_t *);
void queueDestroy(task_queue_t*);
int queueIsEmpty(task_queue_t *);
int getTaskSize(task_queue_t *);
void taskEnqueue(task_queue_t*, int peerfd);
int taskDequeue(task_queue_t*);
void queueWakeup(task_queue_t*);
 
#endif
