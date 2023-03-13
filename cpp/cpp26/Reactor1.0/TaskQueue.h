#ifndef __TaskQueue_H__
#define __TaskQueue_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using std::queue;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    bool empty() const;
    bool full() const;
    void push(const int &value);
    int pop();

private:
    size_t _queSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _flag;
};





#endif
