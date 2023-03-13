#ifndef _THREAD_H
#define _THREAD_H
#include "NonCopyable.h"
#include <pthread.h>
#include <functional>

using std::function;

class Thread 
:NonCopyable
{
    using ThreadCallback = function<void()>;
public: 
    
    Thread(ThreadCallback &&cb);

    
    ~Thread();
    
    void start();
    
     void join();

private:
    static void * threadFunc(void *arg);
private: 
    pthread_t _thid;
    bool _isRunning;
    ThreadCallback _cb;
};

#endif //_THREAD_H
