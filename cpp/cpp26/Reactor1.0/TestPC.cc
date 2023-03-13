#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

void test()
{
    TaskQueue taskQueu(10);

    unique_ptr<Thread> pro(new Producer(taskQueu));
//    unique_ptr<Thread> pro2(new Producer(taskQueu));
    unique_ptr<Thread> con(new Consumer(taskQueu));

    pro->start();
  //  pro2->start();
    con->start();

    pro->join();
   // pro2->join();
    con->join();
}


int main(void)
{
    test();
    return 0;
}


