#ifndef __Condition_H__
#define __Condition_H__

#include "NonCopyable.h"
#include <pthread.h>

class MutexLock;//类的前向声明

class Condition
:NonCopyable
{
public:
    Condition(MutexLock  &mutex);
    ~Condition();
   void  wait();
   void notify();
   void notifyAll();

private:
    MutexLock &_mutex;
    pthread_cond_t _cond;
};







#endif
