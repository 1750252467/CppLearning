#include "Observer.hpp"
#include "Subject.hpp"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

void test()
{
    Ring ring;
    unique_ptr<Observer> baby1(new Baby("可莉"));
    unique_ptr<Observer> baby2(new Baby("纳西妲"));

    unique_ptr<Observer> nurse1(new Nurse("神里"));
    unique_ptr<Observer> nurse2(new Nurse("妮露"));
    unique_ptr<Guest> guest(new Guest("万叶"));
    
    ring.attach(baby1.get());
    ring.attach(baby2.get());
    ring.attach(nurse1.get());
    ring.attach(nurse2.get());
    
    guest->knockAt(ring);


    cout << "\n第二次敲门！" << endl;

    ring.detach(nurse1.get());
    guest->knockAt(ring);
}


int main(void)
{
    test();
    return 0;

}
