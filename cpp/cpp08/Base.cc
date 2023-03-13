#include <iostream>
using std::cout;
using std::endl;

class Base
{

public:
    Base(int i)
    :_i(i)
    {
        cout<<"Base()"<<endl;
    }

    friend int operator+(const Base &i,const Base &j);

private:
    int _i;

};


int operator+(const Base &i,const Base &j)
{
    return (-i._i)+j._i;
}

void test0()
{
    int i=2,j=7;
    Base x(i);
    Base y(j);
    cout<<(x+y == j-i)<<endl;
}



int main(void){

    test0();
    return 0;
}
