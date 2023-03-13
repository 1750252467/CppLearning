#include <math.h>
#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::multiset;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem :con)
    {
        cout << elem << " ";
    }
    cout << endl;
}

void test()
{

}


int main()
{
    multiset<int> number = {1,8,9,6,7,7,7,7,2,4,8,5};

    display(number);

    cout << endl;
#if 1
    auto it3 = number.lower_bound(7);
    cout<<*it3<<endl;

    auto it4 = number.upper_bound(7);
    cout<<*it4<<endl;

    while(it3 != it4)
    {
        cout<<*it3<<endl;
        it3++;
    }
#endif
    cout << endl; 
#if 1
    std::pair<multiset<int>::iterator,multiset<int>::iterator>
        ret = number.equal_range(7);

    while(ret.first != ret.second)
    {
        cout<< *ret.first << " ";
        ++ret.first;
    }

#endif
    cout << endl;
    return 0;
}


