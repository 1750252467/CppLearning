#include <func.h>

int global = 0;

void *thread_func(void *arg){
   global+=20000000;
    return NULL;
}

int main(int argc,char *argv[]){
    pthread_t tid1,tid2;
    int err;
    err = pthread_create(&tid1,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(err,"pthread_create");

    err = pthread_create(&tid2,NULL,thread_func,NULL);
    THREAD_ERROR_CHECK(err,"pthread_create");
    
    void *tret;
    err = pthread_join(tid1,&tret);
    THREAD_ERROR_CHECK(err,"pthread_join");


    err = pthread_join(tid2,&tret);
    THREAD_ERROR_CHECK(err,"pthread_join");

    printf("global = %d\n",global);

    return 0;
}
