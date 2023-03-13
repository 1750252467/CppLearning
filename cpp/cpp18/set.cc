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
        cout << elem << " ";
    }
    cout << endl;
}

void test()
{
    set<int> number = {1,8,9,6,7,5,4,8,7,2,5 };
    display(number);

    cout << endl << "set的查找操作" << endl;

    size_t cnt1 = number.count(8);
    size_t cnt2 = number.count(10);

    cout << cnt1 << endl;
    cout << cnt2 << endl;


    auto it = number.find(7);
    if(it == number.end())
    {
        cout << "该元素不存在set中" << endl;
    }else{
        cout << "*it= " << *it << endl;
    }

    cout << endl << "set的插入操作" << endl;
    std::pair<set<int>::iterator,bool> ret = number.insert(3);

    if(ret.second)
    {
        cout << "插入成功" << *ret.first << endl;
    }
    else
    {
        cout << "该元素插入失败" << endl;
    }
    display(number);

    cout << endl;
    
    






}

int main(void)
{
    test();
    return 0;
}
