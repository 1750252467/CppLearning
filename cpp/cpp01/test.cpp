#include<iostream>
using std::cout;
using std::endl;
namespace wd
{
int number =10;

void display(){
    cout<<"wd::display() number:"<<endl;
}
}

using wd::number;
using wd::display;

void test0(){
    cout<<"number"<<number<<endl;
}
int main(void){
    test0();
    display();
    return 0;
}
