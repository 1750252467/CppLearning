#include <func.h>

#define NHASH 29
#define HASH(id) ((unsigned long)id % NHASH)

struct foo *table[NHASH];

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
    int ref_count;
    int id;
    pthread_mutex_t mutex;
    //protect by hashlock
    struct foo* next;
    //more stuff here
};

struct foo *alloc_foo(int id){
    struct foo* fp=(struct foo*)malloc(sizeof(struct foo));
    if(fp == NULL){
        return NULL;
    }
    fp->ref_count = 1;
    fp->id = id;
    int err = pthread_mutex_init(&fp->mutex,NULL);
    if(err != 0){
        free(fp);
        return NULL;
    }

    //把创建的对象放入hash表中，其他线程是可以访问到创建的对象的
    int idx = HASH(id);
    pthread_mutex_lock(&hashlock);
    fp->next = table[idx];
    table[idx] = fp;
    //必须在释放hashlock之前上锁
    pthread_mutex_lock(&fp->mutex);
    //hashlock 应尽快释放，否则会影响性能
    pthread_mutex_unlock(&hashlock);
    //continue initialize other stuff
    
    pthread_mutex_unlock(&fp->mutex);
    return fp;

}

struct foo* hold_foo(struct foo*fp){
    pthread_mutex_lock(&fp->mutex);
    if(fp->ref_count == 0){
        pthread_mutex_unlock(&fp->mutex);
        return NULL;
    }
    fp->ref_count++;
    pthread_mutex_unlock(&fp->mutex);
    return fp;
}

struct foo* find_foo(int id){
    struct foo* fp;
    pthread_mutex_lock(&hashlock);
    for(fp = table[HASH(id)];fp != NULL;fp = fp->next){
        if(fp->id == id){
            fp =hold_foo(fp);
            break;
        }
    }
    pthread_mutex_unlock(&hashlock);
    return fp;
}

void release_foo(struct foo*fp){
    pthread_mutex_lock(&fp->mutex);
    if(fp->ref_count == 1){
        //last reference
        //保证上锁的顺序，避免死锁现象
        pthread_mutex_unlock(&fp->mutex);
        //这个位置会存在一个时间窗口
        pthread_mutex_lock(&hashlock);
        pthread_mutex_lock(&fp->mutex);

        //recheck the condition
        if(fp->ref_count>1){
            fp->ref_count--;
            pthread_mutex_unlock(&fp->mutex);
            pthread_mutex_unlock(&hashlock);
            return;
        }
        //remove from hash table
        int idx = HASH(fp->id);
        struct foo* prev = table[idx];
        if(prev == fp){
            table[idx] = fp->next;
        }else{
            while(prev->next != fp){
                prev = prev->next;
            }
            prev->next = fp->next;
        }
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_unlock(&fp->mutex);
        pthread_mutex_destroy(&fp->mutex);
        free(fp);
    }else{
        fp->ref_count--;
        pthread_mutex_unlock(&fp->mutex);
    }

}
