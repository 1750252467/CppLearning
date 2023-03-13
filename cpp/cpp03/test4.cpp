#include<iostream>
using std::cout;
using std::endl;

class A
{
public:
    ~A()
    {
        cout<<"A"<<endl;
    }
};

class B
{
public:
    ~B()
    {
        cout<<"B"<<endl;
    }
};

class C
{
public:
    ~C(){
        cout<<"C"<<endl;
    }
};


class D
{
public:
    ~D(){
        cout<<"D"<<endl;
    }
};
C c;
int  main(void)
{
    A *pa=new A();
    B b;
    static D d;
    delete pa;
    return 0;
}
