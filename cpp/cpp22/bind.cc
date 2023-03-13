#include <iostream>
#include <functional>
using std::move;
using std::cout;
using std::endl;
using std::bind;
using std::function;

int add(int a, int b)
{
    cout << " int add(int,int)" << endl;
    return a+b;
}

class Example
{
public:
    int add(int a, int b)
    { 
        cout << "int Example::add(int,int)" << endl;
        return a+b;

    }

  int data = 100;
};

void test()
{
    function<int()> f = bind(add,1,2);
    cout << "f()" << f() << endl;

    Example ex;

    function<int()> f2 = bind(&Example::add,ex,3,5);
    cout << "f2() = " << f2() << endl;

    function<int()> f1 = bind(add,1,2);
    cout << "f()" << f1() << endl;

    function<int(int)>  f3 = bind(add, 4, std::placeholders::_1);
    cout << "f3(5) i=" << f3(5) << endl;

     f =bind(&Example::data,&ex);
    cout << "f()" << f() << endl;
}

void func4(int x1, int x2, int x3, const int &x4, int x5)
{
    cout << "x1 = " << x1 << endl
         << "x2 = " << x2 << endl
         << "x3 = " << x3 << endl
         << "x4 = " << x4 << endl
         << "x5 = " << x5 << endl;
}

void test3()
{
    int number = 10;
    auto f = bind(func4, 1, std::placeholders::_3, 
                  std::placeholders::_1, std::cref(number), number);
    number = 30;
    f(50, 40, 60, 70, 90, 80);//没有用到的参数就丢掉
    
}
int main(void)
{
    test();
    return 0;
}
