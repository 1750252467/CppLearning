
#include "taskqueue.h"
#include <func.h>
 
void queueInit(task_queue_t * que)
{
	if(que) {
		que->pFront = NULL;
		que->pRear = NULL;
		que->queSize = 0;
		que->exitFlag = 0;
		int ret = pthread_mutex_init(&que->mutex, NULL);
		THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

		ret = pthread_cond_init(&que->cond, NULL);
		THREAD_ERROR_CHECK(ret, "pthread_cond_init");
	}
}

void queueDestroy(task_queue_t* que)
{
	if(que) {
		int ret = pthread_mutex_destroy(&que->mutex);
		THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy");

		ret = pthread_cond_destroy(&que->cond);
		THREAD_ERROR_CHECK(ret, "pthread_cond_destroy");
	}
}

int getTaskSize(task_queue_t * que)
{	return que->queSize;	}

int queueIsEmpty(task_queue_t *que)
{	return que->queSize == 0;	}

//入队操作
void taskEnqueue(task_queue_t* que, int peerfd)
{
	int ret = pthread_mutex_lock(&que->mutex);
	THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");
	task_t * ptask = (task_t*)calloc(1, sizeof(task_t));
	ptask->peerfd = peerfd;
	ptask->pnext = NULL;
	if(queueIsEmpty(que)) {
		que->pFront = que->pRear = ptask;
	}else {
		que->pRear->pnext = ptask;	
		que->pRear = ptask;
	}
	++que->queSize;
	ret = pthread_mutex_unlock(&que->mutex);
	THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");
	//通知消费者线程取任务
	ret = pthread_cond_signal(&que->cond);
}

//出队操作
int taskDequeue(task_queue_t * que)
{
	int ret = pthread_mutex_lock(&que->mutex);
	THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");
	//当队列为空时，进入等待状态
	while(!que->exitFlag && queueIsEmpty(que)) {//防止虚假唤醒(高频考点)
		pthread_cond_wait(&que->cond, &que->mutex);
	}

	int fd = -1; 
	if(!que->exitFlag) {//不退出线程池时,要取任务节点
		task_t * pFree = NULL;//保存待释放的节点
		fd = que->pFront->peerfd;
		pFree = que->pFront;
		if(getTaskSize(que) > 1) {
			que->pFront = que->pFront->pnext;
		} else {
			pFree = que->pFront;
			que->pFront = que->pRear = NULL;
		}
		free(pFree);
		--que->queSize;
	}
	ret = pthread_mutex_unlock(&que->mutex);
	THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");

	return fd;
}

void queueWakeup(task_queue_t* que) 
{
	que->exitFlag = TASKQUEUE_READY_EXIT_FLAG;
	int ret = pthread_cond_broadcast(&que->cond);
	THREAD_ERROR_CHECK(ret, "pthread_cond_broadcast");
}

