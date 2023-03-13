#include <iostream>

using std::cout;
using std::endl;

class B
{
public:
	B()
	{
        cout << "B()" << endl;
    }

    ~B()
    {
    	cout << "~B()" << endl;
    }
    
    B(const B &rhs)
    {
        cout << "B(const B&)" << endl;
    }
    
    B &operator=(const B &rhs)
    {
    	cout << "B &operator=(const B &s)" << endl;
    
        return  *this;
    }
};

B func(const B &rhs)
{
    cout << "B func(const B &)" << endl;
    return rhs;
}


int main(int argc, char **argv)
{
	B b1,b2;
    b2=func(b1);//10#

	return 0;
}
