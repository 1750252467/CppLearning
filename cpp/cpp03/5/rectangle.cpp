#include<iostream>
using std::cout;
using std::endl;

class Rectangle
{
public:
    Rectangle(int length,int width)
    :_length(length)
    ,_width(width)
    {}
    int perimeter(Rectangle *r);
    int area(Rectangle *r);
    void print(Rectangle *r);
private:
    int _length;
    int _width;
};

int Rectangle::perimeter(Rectangle *r){
    return 2*(r->_length+r->_width);
}

int Rectangle::area(Rectangle *r){
    return r->_length*r->_width;
}

void Rectangle:: print(Rectangle *r){
    
   cout<<"周长："<< r->perimeter(r)<<endl;
   cout<<"面积："<<r->area(r)<<endl;
   cout<<endl;
}
int main(){
    Rectangle A(4,5);
    Rectangle B(3,7);
    
    cout<<"A"<<endl;
    A.print(&A);
    cout<<"B"<<endl;
     B.print(&B);
    return 0;
}
