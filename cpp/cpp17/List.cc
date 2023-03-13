#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

int main(void){
list<int> lst;
list<int>::iterator iter1 = lst.begin(), iter2 = lst.end();
while(iter1 < iter2)
{
    //....
}
}
