#ifndef _THREAD_H
#define _THREAD_H
#include "NonCopyable.h"
#include <pthread.h>
#include <functional>

using std::function;

class Thread 
:NonCopyable
{
public: 
    
    Thread();

    
    virtual ~Thread();
    
    void start();
    
     void join();

private:
    static void * threadFunc(void *arg);
     virtual void run() = 0;
private: 
    pthread_t _thid;
    bool _isRunning;
};

#endif //_THREAD_H
