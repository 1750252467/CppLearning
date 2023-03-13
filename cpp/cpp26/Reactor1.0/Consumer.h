#ifndef __Consumer_H__
#define __Consumer_H__

#include "Thread.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

class Consumer
:public Thread
{
public:
    Consumer(TaskQueue &taskQue)
    :_taskQue(taskQue)
    {
            
    }

    ~Consumer(){}

    void run() override
    {
        while(1)
        {
            int number = _taskQue.pop();
            cout << "Consumer number= " << number << endl << endl;
            sleep(1);
        }
    }

private:
    TaskQueue &_taskQue;
};





#endif
