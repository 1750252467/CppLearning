#include<iostream>
using std::cout;
using std::endl;

class Point
{

public:
    Point()
    {
        cout<<"Point(int x=0,int y=0)"<<endl;
    //    _ix=0;
      //  _iy=0;
    }

    Point(int x=0,int y=0)
    :_ix(x),_iy(y)
    {
       // _ix= x;
       // _iy=y;
    }
    void print(){
        cout<<"("<<_ix
            <<","<<_iy
            <<endl;
    }


private:
    int _ix;
    int _iy;
};

void test0(){
    Point pt();
    pt().print();

    Point pt3(3,4);
    pt3.print();
}

int main(void){
    
    test0();
    return 0;
}
