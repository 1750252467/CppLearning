#include "ThreadPool.h"
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
:_threadNum(threadNum)
,_queSize(queSize)
,_taskQue(queSize)
,_isExit(false)
{
    _threads.reserve(threadNum);
}

ThreadPool::~ThreadPool()
{
    if(!_isExit)
    {
        stop();
        _isExit = true;
    }
}

void ThreadPool::start()
{
    for(size_t idx = 0; idx < _threadNum; ++idx)
    {
        unique_ptr<Thread> up(new Thread(std::bind(&ThreadPool::threadFunc,this)));
        _threads.push_back(std::move(up));
    }

    for(auto &th : _threads)
    {
        th->start();
    }
}

void ThreadPool::stop()
{

    while(!_taskQue.empty())
    {
        sleep(1);
    }

    _isExit = true;
    _taskQue.wakeup();

    for(auto &th : _threads)
    {
        th->join();
    }
}

void ThreadPool::addTask(Task &&task)
{
    if(task)
    {
        _taskQue.push(std::move(task));
    }
}

Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

void ThreadPool::threadFunc()
{
    while(!_isExit)
    {
        Task taskcb = getTask();
        if(taskcb)
        {
            taskcb();
        }
    }
}
