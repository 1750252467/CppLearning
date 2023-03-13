
 
#include "threadpool.h"
 
void threadpoolInit(thread_pool_t* pthreadpool, int threadNum)
{
	pthreadpool->threadNumber = threadNum;
	pthreadpool->threads = (pthread_t*)calloc(threadNum, sizeof(pthread_t));
	queueInit(&pthreadpool->queue);
}

void threadpoolDestroy(thread_pool_t* pthreadpool)
{
	free(pthreadpool->threads);
	queueDestroy(&pthreadpool->queue);
}

void threadpoolStart(thread_pool_t * pthreadpool)
{
	for(int idx = 0; idx < pthreadpool->threadNumber; ++idx) {
		int ret = pthread_create(&pthreadpool->threads[idx],
			NULL, 
			threadFunc, 
			pthreadpool);
		THREAD_ERROR_CHECK(ret, "pthread_create");
	}
}

void * threadFunc(void* arg)
{
	//每一个子线程要做的事儿
	printf("sub thread %ld is runing\n", pthread_self());
	thread_pool_t * pthreadpool = (thread_pool_t*)arg;
	while(1) {
		int peerfd = taskDequeue(&pthreadpool->queue);
		if(peerfd > 0) {
			char filename[] = "bigfile.avi";
			transferfile(peerfd, filename);
		} else {
			break;
		}
	}
	printf("sub thread %ld is ready to exit\n", pthread_self());
	pthread_exit(0);
}
