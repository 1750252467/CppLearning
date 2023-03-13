#include <iostream>
#include <functional>

using std::cout;
using std::endl;

int add(int x,int y)
{
    cout<<"and()"<<endl;
    return x+y;
}


int mulity(int x,int y)
{
    cout<<"mulity()"<<endl;
    return x*y;
}

class Foo
{
public:
    int add(int x,int y)
    {
        cout<<"Foo::add()"<<endl;
        return x+y;
    }

    int multiply(int x,int y)
    {
        cout<<"Foo::multiply()"<<endl;
        return x*y;
    }


};

typedef int(*Function)(int,int);

typedef int(Foo::*MemberFunction)(int,int);

void test0()
{
    Function f =add;
    cout<<"f(3,4)"<<f(3,4)<<endl;

    MemberFunction f1 = &Foo::add;
    
    Foo foo;
    cout<<(foo.*f1)(3,4)<<endl;
    Foo *fp = &foo;
    cout<<(fp->*f1)(3,4)<<endl;
}

class FunctionObject
{
public:
    
    void operator()(int x)
    {
        ++_count;
        cout<<"x:"<<x<<endl;
    }

    int operator()(int x,int y)
    {
        cout<<"operator()()"<<endl;
        ++_count;
        return x+y;

    }



    int _count = 0;
};


void test1()
{
    std::function<int(int,int)>f;

    f = add;
    cout<<"f(3,4)"<<f(3,4)<<endl;
    f = mulity;
    cout<<"f(3,4)"<<f(3,4)<<endl;

    Function fo = add;
    f = fo;
    cout<<"f(3,4)"<<f(3,4)<<endl;

    Foo foo;

    using namespace std::placeholders;
    
     f = std::bind(&Foo::multiply,&foo,_1,_2);
    cout<<"f(3,4)"<<f(3,4)<<endl;

    FunctionObject f1;

    f = f1;

    cout<<"f(3,4)"<<f(3,4)<<endl;

}

int main(void){
    test1();
    return 0;

}






