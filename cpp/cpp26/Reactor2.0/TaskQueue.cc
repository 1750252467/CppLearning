#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_que()
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
,_flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

bool TaskQueue::empty() const
{
    return 0 == _que.size();
}
bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}
void TaskQueue::push(ElemType value)
{
    MutexLockGuard autoLock(_mutex);//栈对象
   /* _mutex.lock(); */
    //虚假唤醒
    /* if(full()) */
    while(full()){
        _notFull.wait();
    }
    _que.push(value);

    _notEmpty.notify();
}

ElemType TaskQueue::pop()
{ //RAII的思想：利用栈对象的生命周期进行管理资源
    MutexLockGuard autoLock(_mutex);//栈对象
    while(_flag &&empty()){
        _notEmpty.wait();

    }
    if(_flag)
    {
        
    ElemType tmp = _que.front();
    _que.pop();

    _notFull.notify();
    return tmp;
    }else
    {
        return nullptr;
    }


}

void TaskQueue::wakeup()
{

    _flag = false;
    _notEmpty.notifyAll();
}

