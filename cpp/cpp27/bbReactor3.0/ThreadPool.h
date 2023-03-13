#ifndef __ThreadPool_H__
#define __ThreadPool_H__

#include "Thread.h"
#include "TaskQueue.h"

#include <vector>
#include <memory>
#include <functional>

using std::vector;
using std::unique_ptr;
using std::function;

using Task = function<void()>;

class ThreadPool
{

    friend class WorkThread;
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();

    void addTask(Task &&task);
private:
    Task getTask();
    void threadFunc();

private:
    size_t _threadNum;
    size_t _queSize;
   vector<unique_ptr<Thread>>  _threads;
   TaskQueue _taskQue;
   bool _isExit;
};





#endif
