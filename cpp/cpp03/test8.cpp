#include <iostream>

using std::cout;
using std::endl;

class Base
{
	float _ix;
	float _iy;
public:
    Base(float ix,float iy)
    {
        _ix = ix;
        _iy = iy;
    }
 	
    float gain();
};

float Base:: gain()
{ 
	return _iy/_ix; 
}

int main()
{
	Base base(5.0,10.0);
 	cout << "The gain is => " << base.gain() << endl;
    
    return 0;

}
