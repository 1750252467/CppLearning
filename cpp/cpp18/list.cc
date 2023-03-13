#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem :con)
    {
        cout << elem << " ";
    }
    cout << endl;
}

template <typename T>
struct Com
{
    bool operator()(const T &lhs, const T &rhs) const
    {
        return lhs > rhs ;
    }
};
#if 0
bool operator<(const list<int> &lhs, const list<int> &rhs)
{
    return lhs > rhs;

}
#endif


namespace std
{
template <>
struct less<list<int>>
{
    bool operator()(const list<int> &lhs, const list<int> &rhs) const
    {
        return  lhs > rhs;
    }
};

}

void test()
{
    list<int> number = {1,3,3,5,9,4,4,3,2,10};
    display(number);

    cout << endl << "测试list merge操作" <<endl;
    list<int> number2 = {1,20,30,50,15};
    number.sort();
    number2.sort();
    number.merge(number2);
    display(number);
    display(number2);
    
    number.unique();
    display(number);

    number.reverse();
    display(number);

    number.sort();
    display(number);

    number.sort(Com<int>());
    display(number);
    
    cout << "list splice " << endl;

    list<int> number3 = {5,22,33,11};
    auto it = number.begin();
    ++it;;
    number.splice(it,number3);
    display(number);
    display(number3);

    cout << endl << endl;
    list<int> number4 = {55,66,88,77};
    auto it4 =number4.begin();
    it = number.begin();
    ++it;
    number.splice(it,number4,it4);
    display(number);
    display(number4);

    list<int> number5 ={100,300,500,400,900,700};
    auto it5 = number5.begin();
    ++it5;
    auto it6 = number5.end();
    --it6;
    --it6;
    number.splice(it,number5,it5,it6);
    display(number);
    display(number5);

    auto it7 = number.begin();
    ++it7;

    auto it8 = number.end();
    --it8;
    cout << *it7 << endl;
    cout << *it8 << endl;
    number.splice(it7,number,it8);
    display(number);
    
    cout<<*it8<<endl;

    *it8 =10;
    
    cout<<*it8<<endl;




}

int main(void)
{
    test();
    return 0;
}





