#include <iostream>
#include <vector>
#include <deque>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;

template <typename Container>
void display(const Container &con)
{   
    for(auto &elem :con)
    {
        cout<<elem<<" ";
    }
    cout<<endl;
}

void test()
{   cout<<"vector test"<<endl<<endl;
    cout<<"初始化"<<endl<<endl;
    
    vector<int> number1;
    display(number1);

    vector<int> number2(10,2);
    display(number2);

    int arr[10] = {1,3,4,2,5,0,9,7,8,6};
    vector<int> number3(arr,arr+10);
    display(number3);

    vector<int> number4 = {1,0,33,22,888,99,521,10,33,2};
    display(number4);
    
    cout << "vector尾部的插入与删除" << endl << endl;
    
    number4.push_back(666);
    display(number4);
    number4.push_back(666);
    display(number4);
    number4.pop_back();
    display(number4);

    cout<< "vector 的插入与删除" << endl << endl;

    vector<int> number ={1,2,3,4,5,6,6,6,6,6,9,6,6,6};
    display(number);

    for(auto it = number.begin(); it != number.end();)
    {
        if(*it == 6)
        {
            number.erase(it);
        }
        else
        {
            ++it;
        }
    }
    display(number);
    
    cout << "元素的清空" << endl << endl; 

    number.clear();
    number.shrink_to_fit();

    cout << "number.size()" << number.size() << endl;
    cout << "number.capacity()" << number.capacity() <<endl;


}

int main(void){
    test();
    return 0;
}












