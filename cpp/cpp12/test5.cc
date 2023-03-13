#include<iostream>

using std::endl;
using std::cout;

class Base1
{
public:
    virtual void fun()       
    {   
		cout<<"--Base1--\n";  
	}
};

class Base2
{
public:
    void fun()               	
    {   
		cout<<"--Base2--\n"; 
	}
};

class Derived
:public Base1
,public Base2
{
public:
    void fun()
    {   
        cout<<"--Derived--\n";  
    }
};

int main()
{
    Base1 obj1, *ptr1;   
    Base2 obj2, *ptr2;   	
    Derived obj3; 
	

    ptr1=&obj1;         	
    ptr1->fun(); 
    
    ptr2=&obj2;         	
    ptr2->fun(); 
    
    ptr1=&obj3;         	
    ptr1->fun(); 
    
    ptr2=&obj3;         	
    ptr2->fun(); 
    
    return 0;	                  

}
