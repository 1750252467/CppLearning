#include <stdio.h>
class A
{
public:
 void FuncA()
 {
     printf( "FuncA called\n" );
 }
 virtual void FuncB()
 {
     printf( "FuncB called\n" );
 }
};

class B 
: public A
{
public:
 void FuncA()
 {
     A::FuncA();
     printf( "FuncAB called\n" );
 }
    
 virtual void FuncB()
 {
     printf( "FuncBB called\n" );
 }
};

int main( void )
{
	B	b;
	A	*pa;
	pa = &b;
	A *pa2 = new A;
	pa->FuncA();  
	pa->FuncB(); 
	pa2->FuncA(); 
	pa2->FuncB();
	delete pa2;
	

	return 0;

}
