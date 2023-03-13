#include <vector>
#include <memory>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

class Point
{
public:
    Point(int x,int y)
    :_ix(x),_iy(y)
    { cout<<"Point(int,int)"<<endl;}

    ~Point(){ cout<<"~Point"<<endl;}

    void print() const{
        cout<<"("<<_ix<<","<<_iy<<")"<<endl;
    }

    friend std::ostream & operator<<(std::ostream &os,const Point &rhs);
private:
    int _ix,_iy;

};

std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
    os<<"("<<rhs._ix<<","<<rhs._iy<<")";
    return os;
}

void test0()
{
    shared_ptr<Point> sp(new Point(1,2));
    cout<<sp.get()<<endl;
    cout<<*sp<<endl;
    cout<<sp.use_count()<<endl;
    sp->print();
    (*sp).print();


}
int main(void){
    test0();
    return 0;
}