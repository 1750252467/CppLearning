#include<iostream>
using std::cout;
using std::endl;

namespace wd
{
void fun(int a,int b=0){

}

void fun(){}

void fun(int a=0){

}

void fun(int a=0,int b=0,int c =1){
        cout<<a <<b <<c<<endl;


}
}
using namespace  wd;

int main(void){
    fun(1,1,1);
    return 0;
}

