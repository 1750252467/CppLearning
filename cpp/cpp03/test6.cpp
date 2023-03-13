#include <iostream>

using std::cout;
using std::endl;

struct  Foo
{

	Foo()
	{
	}
	

	Foo(int)
	{
	}
	
	void fun()
	{
	}

};

int main(void)
{
	Foo a(10);//语句1
	a.fun();//语句2
	Foo b;//语句3
	b.fun();//语句4 
	return 0;
}
