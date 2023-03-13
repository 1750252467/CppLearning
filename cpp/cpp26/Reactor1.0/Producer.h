#ifndef __Producer_H__
#define __Producer_H__

#include "Thread.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

class Producer
:public Thread
{
public:
    Producer(TaskQueue &taskQue)
    :_taskQue(taskQue)
    {

    }
    ~Producer()
    {

    }

    void run() override
    {
        ::srand(clock());
        int cnt = 20;
        while(cnt--> 0)
        {
            int number = ::rand()%100;
            _taskQue.push(number);
            cout << ">>producer number = " << number << endl << endl;
            sleep(1);
        }
    }
private:
    TaskQueue &_taskQue;
};




#endif
