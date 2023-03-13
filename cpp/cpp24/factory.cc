#include <math.h>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::string;

class Figure
{
public:

    virtual string getName() const = 0;
    virtual double getAre() const = 0;
    virtual ~Figure() {}

};

void display(Figure *fig)
{
    cout << fig->getName() << "的面积是：";
    cout << fig->getAre() << endl;
}

class Circle
:public Figure 
{
public:
    Circle(double radius)
    :_radius(radius)
    {}

    string getName() const override
    { return string("圆"); }

    double getAre() const override
    {
        return PI * _radius *_radius;
    }

private:

    double _radius;
    static constexpr double PI = 3.14159;
};

class Rectangle
:public Figure
{
public:
    Rectangle(double length,double width)
    :_length(length)
     ,_width(width)
    {}

    string getName() const override
    { return string("矩形"); }

    double getAre() const override
    {
        return _length *_width;
    }
private:
    double _length;
    double _width;
};

class Triangle
:public Figure
{
public:
    Triangle(double a,double b,double c)
    :_a(a),_b(b),_c(c)
    {}

    string getName() const override
    { return string("三角形"); }

    double getAre() const override
    {
        double p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }
private:
    double _a,_b,_c;
};



//工厂模式
class Factory
{
public:
    virtual Figure * create() = 0;
    virtual ~Factory() {}
};

class CircleFactory
: public Factory
{
public:
    Figure * create() override
    {
        //
        return new Circle(10);
    }
};

class RectangleFactory 
: public Factory
{
public:
    Figure *create() override
    {
        //
        return new Rectangle( 10, 20);
    }
};

class TriangleFactory
: public Factory
{
public:
    Figure * create()override
    {
       return  new Triangle(3, 4, 5);
    }
};


class Demo
{
public:
    Demo(Factory * pFac)
    :_pFactory(pFac)
    {}

    void print()
    {
        //
        //
        display(_pFactory->create());
    }

    Factory * _pFactory;
};


void test0()
{
    cout << "Factory Pattern" << endl;
    //
    unique_ptr<Factory> circleFac(new CircleFactory());
    unique_ptr<Figure> circle(circleFac->create());
    
    unique_ptr<Factory> rectangleFac(new RectangleFactory());
    unique_ptr<Figure> rectangle(rectangleFac->create());

    unique_ptr<Factory> triangleFac(new TriangleFactory());
    unique_ptr<Figure> triangle(triangleFac->create());

    display(circle.get());
    display(rectangle.get());
    display(triangle.get());

    Demo demo(new CircleFactory());
    demo.print();

}

int main()
{
    test0();
    return 0;
}
