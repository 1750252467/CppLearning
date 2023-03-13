#include <func.h>

typedef struct sharedRes_s{
    pthread_mutex_t mutex1;

    pthread_mutex_t mutex2;
} shareRes_t; 

void *threadFunc(void *arg){
    puts("I am child thread"); 

}
int main() {
    shareRes_t shared;
    pthread_t tid;

    pthread_mutex_init(&shared.mutex1,NULL);
    
    pthread_mutex_init(&shared.mutex2,NULL); 
    pthread_create(&tid,NULL,threadFunc,&shared);

    
 
    pthread_mutex_lock(&shared.mutex1); 
    pthread_mutex_lock(&shared.mutex2); 
    sleep(2);
    pthread_mutex_unlock(&shared.mutex1); 
    pthread_mutex_unlock(&shared.mutex2); 
    pthread_join(tid,NULL);
    puts("I am main thread"); 
    return 0;
}
