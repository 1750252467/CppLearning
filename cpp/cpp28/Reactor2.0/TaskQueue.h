#ifndef __TaskQueue_H__
#define __TaskQueue_H__

#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"
#include <queue>

using std::queue;

using ElemType = Task *;


class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    bool empty() const;
    bool full() const;
    void push(ElemType value);
    ElemType pop();

    void wakeup();

private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _flag;
};





#endif
