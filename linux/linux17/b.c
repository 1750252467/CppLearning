 #include<func.h>                                                     

 pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t mutex2=PTHREAD_MUTEX_INITIALIZER;

void*thread1(void*arg)
 {
   printf("thread1 exit...\n");
   pthread_mutex_lock(&mutex1);//申请锁1
    printf("thread1 catch mutex1\n");
   
    pthread_mutex_lock(&mutex2);//申请锁2
    printf("thread1 catch mutex2\n");
   pthread_mutex_unlock(&mutex1);
    printf("thread1 release mutex1\n");
     pthread_mutex_unlock(&mutex2);
   printf("thread1 release mutex2\n");
 
 }

 void*thread2(void*arg)
 {
     printf("thread2 exit...\n");
     pthread_mutex_lock(&mutex1);//申请锁1
     printf("2 catch mutex2\n");
   
     pthread_mutex_lock(&mutex2);//申请锁2
     printf("2 catch mutex1\n");
    pthread_mutex_unlock(&mutex1);
    printf("2 re mutex1\n");
    pthread_mutex_unlock(&mutex2);
     printf("2 re mutex2\n");
}

 int main(void)
 {
     pthread_t tid1,tid2;
    int err=pthread_create(&tid1,NULL,thread1,NULL);
     THREAD_ERROR_CHECK(err,"pthread_create");
 
    err=pthread_create(&tid2,NULL,thread2,NULL);
    THREAD_ERROR_CHECK(err,"pthread_create");

    void*tret;
     err=pthread_join(tid1,&tret);
     THREAD_ERROR_CHECK(err,"pthread_join");

    err=pthread_join(tid2,&tret);
	THREAD_ERROR_CHECK(err,"pthread_join");
 }      
