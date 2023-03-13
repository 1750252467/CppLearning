#include <func.h>

pthread_t ntid;

void printids(const char* msg){
    pid_t pid = getpid();
    //
    pthread_t tid = pthread_self();

    printf("%s: pid %lu, tid %lu (%lx)\n",msg,
           (unsigned long) pid,
           (unsigned long) tid,
           (unsigned long) tid);
}


void  *start_routine(void *arg){
    printids("new thread");
    return NULL;
}

int main(){
    int err = pthread_create(&ntid,NULL,start_routine,NULL);
    if(err != 0){
        fprintf(stderr,"Cannot create thread: %s\n",strerror(err));
    }
        printids("main thread");
        sleep(1);
        return 0;
}
