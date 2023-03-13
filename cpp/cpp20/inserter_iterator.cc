#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using std::cout;
using std::endl;
using std::ostream_iterator;
using std::back_inserter;
using std::back_insert_iterator;
using std::front_inserter;
using std::front_insert_iterator;
using std::inserter;
using std::insert_iterator;
using std::vector;
using std::list;
using std::set;
using std::copy;

void test()
{
    vector<int> vecNumber = {1,2,3};
    list<int> listNumber = {11,33,22};

    copy(listNumber.begin(),listNumber.end(),
         back_inserter(vecNumber));
    copy(vecNumber.begin(),vecNumber.end(),
         ostream_iterator<int>(cout," "));
    cout << endl;

    cout << endl << endl;

    copy(vecNumber.begin(),vecNumber.end(),
         front_insert_iterator<list<int>>(listNumber));
    copy(listNumber.begin(),listNumber.end(),
         ostream_iterator<int>(cout," "));
    


    cout << endl << endl;
    set<int> setNumber = {8,20,400};
    auto it = setNumber.begin();

    copy(vecNumber.begin(),vecNumber.end(),
         insert_iterator<set<int>>(setNumber,it));
    copy(setNumber.begin(),setNumber.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;


}

int main(void)
{
    test();
    return 0;
}
