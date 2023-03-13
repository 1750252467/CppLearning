#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::ostream;
using std::copy;
using std::ostream_iterator;

void print(int &value)
{

    cout << value << " ";
}

void test1()
{
    int a=100;
    vector<int> number = {1,2,3,5,6,5};

    for_each(number.begin(),number.end(),[&a](int &value)->void{
    cout << ++a << " ";
    ++value;
    cout << value << " ";

             });

    
    copy(number.begin(),number.end(),ostream_iterator<int>(cout," "));
    cout <<endl;

}


void display(int value)
{
    cout << value << " ";

}


void test2()
{
    vector<int> number = {1,2,3,5,6,5,5,5,5,5};
    for_each(number.begin(),number.end(),display);
    cout << endl;

    size_t cnt1 = std::count(number.begin(),number.end(),5);
    cout << "cnt1" << cnt1 << " " << endl;

    auto it = std::find(number.begin(),number.end(),5);
    if(it !=number.end())
    {
        cout << *it << endl;


    }else{
        cout << " no" <<endl;
    }


}

int main()
{
    test2();
    return 0;
}
