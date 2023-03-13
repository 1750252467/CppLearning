#include "Thread.h"
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

Thread::Thread(ThreadCallback &&cb)
:_thid(0)
,_isRunning(false)
,_cb(std::move(cb))
{

}

Thread::~Thread() 
{

    if(_isRunning)
    {
        pthread_detach(_thid);
        _isRunning = false;
    }

        cout << "TTTTTTTTTTTTTTTTTTTT" << endl;
}
    //shift + k进行跳转，找到函数的定义
    //threadFunc要设计成静态成员函数，消除this指针影响
    /* int ret = pthread_create(&_thid, nullptr, threadFunc, nullptr); */
void Thread::start()
{
    int ret = pthread_create(&_thid,nullptr,threadFunc,this);
    if(ret){
        perror("pthread_create");
    }
    _isRunning = true;
}

void Thread::join() 
{
    if(_isRunning){
        int ret = pthread_join(_thid,nullptr);
        if(ret){
            perror("pthread_join");
            return;
        }
        _isRunning = false;
    }
}



void * Thread::threadFunc(void  *arg) {

    Thread *pth = static_cast<Thread *>(arg);
    //run是非静态的，而threadFun是静态的
    if(pth)
    {
        pth->_cb();
    }

    return nullptr;
}

