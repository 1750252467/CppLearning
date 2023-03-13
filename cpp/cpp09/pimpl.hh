#include<iostream>

using std::cout;
using std::endl;

class Line
{
public:
    Line(int x1, int y1,int x2, int y2);
    ~Line();
    void printLine() const;

    class LineImpl;
private:
    LineImpl *_pipl;
};
