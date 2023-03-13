#include <iostream>

using std::cout;
using std::endl;

class Sample 
{
	int i;
public:
	Sample();
	Sample(int val);
	void Display();
	~Sample();
};
Sample::Sample() 
{
	cout << "Constructor1" << endl;
	i=0;
}

Sample::Sample(int val) 
{
	cout << "Constructor2" << endl;
    i=val;
}

void Sample::Display() 
{
   cout << "i=" << i << endl;
}

Sample::~Sample() 
{
   cout << "Destructor" << endl;
}

int main() 
{
     Sample a, b(10);
     a.Display();
     b.Display();
	 
     return 0;
}
