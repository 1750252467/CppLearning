#include <iostream>
const double P=3.14;
using std::cout;
using std::endl;

class Circle
{
public:
    Circle():_r(0){}
    
    Circle(double r):_r(r){}

    double getArea()
    {
        return P*_r*_r; 
    }

    double getPerimeter()
    {
        return 2*P*_r;
    }

    void show() 
    {
        cout<<"半径："<<_r<<endl;
        cout<<"周长："<<getPerimeter()<<endl;
        cout<<"面积："<<getArea()<<endl;
    }

private:
    double _r;
};


class Cylinderi
:public Circle
{
public:

    Cylinderi(double r, double h):Circle(r),_h(h){}
    
    double getVolume()
    {
        return getArea()*_h;
    }

    void showVolume()
    {
        cout<<"圆柱的体积为"<<getVolume()<<endl;
    }

private:
    double _h;
};

void test()
{
    Cylinderi C1(2,3);

    C1.show();
    C1.showVolume();
}

int main(){
    test();
    return 0;
}
