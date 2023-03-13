#include <iostream>

using std::cout;
using std::endl;

class Base
{ 
public:
	int a1,a2;

    Base(int x1 = 0, int x2 = 0)
    :a1(x1)
    ,a2(x2)
    {
        
    }
};


int main()
{
	Base data(2,3);
 	cout << data.a1 << endl;
 	cout << data.a2 << endl;
    
    return 0;
}
