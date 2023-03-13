#include<iostream>
using std::cout;
using std::endl;

class Point
{
public:
    static Point *getInstance()
    {
        if(nullptr ==_pInstance){
            _pInstance = new Point();  
        }
        return _pInstance;
    }
    
    static void destroy()
    {
        if(_pInstance){
            delete _pInstance;
        }

    }
    void init(int x,int y){

        _ix = x;
        _iy = y;
    }
    Point(const Point &) = delete;
    void print() const
    {
        cout<<"("<<_ix
            <<","<<_iy
            <<")"<<endl;
    }


private:
    Point(int ix=0,int iy = 0)
    :_ix(ix)
    ,_iy(iy)
    {
        cout<<"Point(int,int)"<<endl;
    }
    ~Point()
    {
        cout<<"~Point()"<<endl;
    }
    int _ix;
    int _iy;
    static Point * _pInstance;
};

Point *Point::_pInstance = nullptr;
void test0(){
    Point *p1 = Point::getInstance();
    Point *p2 = Point::getInstance();

    p1->init(1,2);
    printf("p1:%p\n",p1);
    printf("p2:%p\n",p2);
    
    p1->print();
    p2->print();
    
    Point::destroy();

}

int main(void){
    test0();
    return 0;
}



