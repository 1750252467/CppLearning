#include <iostream>
using std::endl;
using std::cout;

class A
{
public:
	A(int i,int j) 
	{
		a=i;
		b=j;
	}
	void move(int i,int j) 
	{
		a += i;
		b += j;
	}
	void disp() 
	{ 
		cout << "(" << a << "," << b << ")" << endl;
	}
private:
	int a,b;
};

class B
: public A
{
public:
	B(int i,int j,int k,int l)
	:A(i,j)
	,x(k)
	,y(l)
	{ 
	}
	
	void disp() 
	{
		cout << x << "," << y << endl;
	}
	void fun() 
	{
		move(3,5);
	}

private:
	int x,y;
};

int main()
{
	A m(1,2);
	m.disp();
	B d(3,4,5,6);
	d.fun();
	d.A::disp();
	d.disp();
	

	return 0;

}
