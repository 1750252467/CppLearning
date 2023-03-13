#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

void test0(){

    int *p = static_cast<int*>(malloc(sizeof(int)));
    *p = 10;
    cout<<"*p"<<*p<<endl;
}

void func(int *px){

    *px =100;
    cout<<"*px:"<<*px<<endl;

}

void test1(){

    const int number = 10;
    func(const_cast<int*>(&number));
    cout<<"number"<<endl;
}

int main(){
    test0();
    test1();
    return 0;
}
