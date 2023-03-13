#include <math.h>
#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

void test()
{
    //set的特征
    //1、key值是唯一的，不能重复
    //2、默认情况下，会按照key值进行升序排列（std::less）
    //3、set的底层实现采用是红黑树
    set<int> number = {1, 8, 9, 6, 7, 5, 4, 8, 7, 2, 5};
    /* set<int, std::greater<int>> number = {1, 8, 9, 6, 7, 5, 4, 8, 7, 2, 5}; */
    display(number);

    cout << endl << "set的查找操作" << endl;
    size_t cnt1 = number.count(8);
    size_t cnt2 = number.count(10);
    cout << "cnt1 = " << cnt1 << endl;
    cout << "cnt2 = " << cnt2 << endl;

    /* set<int>::iterator it = number.find(7); */
    auto it = number.find(7);
    if(it == number.end())
    {
        cout << "该元素不存在set中" << endl;
    }
    else
    {
        cout << "*it = " << *it << endl;
    }

    cout << endl << "set的插入操作" << endl;
    std::pair<set<int>::iterator, bool> ret = number.insert(3);
    if(ret.second)
    {
        cout << "插入成功 " << *ret.first << endl;
    }
    else
    {
        cout << "该元素插入不成功,该元素已经在set中" << endl; 
    }
    display(number);

    cout << endl << "set的删除" << endl;
    auto it2 = number.begin();
    ++it2;
    number.erase(it2);
    display(number);

    cout << endl << "set的下标访问" << endl;
    /* cout << "number[1] = " << number[1] << endl; */

    cout << endl << "set的修改功能" << endl;
    it = number.begin();
    cout << "*it = " << *it << endl;
    /* *it = 100;//error */
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int = 0, int = 0)" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" <<  rhs._ix
       << ", " << rhs._iy
       << ")";

    return os;
}
#if 0
//命令空间的扩展
//模板的特化(全特化和偏特化)
namespace  std
{

template <>
struct less<Point>
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        /* return lhs < rhs; */
    }
};

}//end of namespace std







//运算符重载
bool operator<(const Point &lhs, const Point &rhs)
{

}
#endif

//函数对象的形式
struct Comparetion
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
    }
};

void test2()
{
    set<Point> number = {
        Point(1, 2),
        Point(-1, 2),
        Point(1, -2),
        Point(3, 2),
        Point(1, 2),
        Point(10, 3)
    };
    display(number);
}
int main(int argc, char **argv)
{
    test2();
    return 0;
}


