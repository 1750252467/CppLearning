#include "pimpl.hh"

class Line::LineImpl
{
private:
    class Point
    {
    public:
        Point(int x,int y)
       :_x(x)
        ,_y(y)
        {}
        void print()const
        {
            cout<<"("<<_x
                <<","<<_y
                <<")";
        }

    private:
        int _x;
        int _y;
    };

public:
    LineImpl(int x1, int y1, int x2, int y2)
    :_p1(x1,y1)
     ,_p2(x2,y2)
    {
        cout<<"LineImpl()"<<endl;
    }
    
    void printLine()const
    {
        _p1.print();
        cout<<"--->";
        _p2.print();
        cout<<endl;
    }
private:
    Point _p1;
    Point _p2;

};

Line::Line(int x1,int y1,int x2,int y2)
:_pipl(new LineImpl(x1,y1,x2,y2))
{
    cout<<"Line()"<<endl;

}


Line::~Line()
{

    if(_pipl){
        delete  _pipl;
        _pipl = nullptr;
    }
}

void Line::printLine()const
{

    _pipl->printLine();
}



