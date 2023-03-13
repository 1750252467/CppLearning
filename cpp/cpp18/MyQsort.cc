#include <math.h>
#include <iostream>
#include <vector>
#include <ostream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

template<typename T>
void swap(T &lhs,T &rhs)
{
    auto temp = lhs;
    lhs = rhs;
    rhs = temp;

}

template<typename T,typename Compare = std::less<T>>
class MyQsort
{
public:
    MyQsort(T *art,size_t size,Compare );
    void quick(int left, int right, Compare &);
    int partition(int left, int right, Compare &);
    void print();
private:
    vector<T> _vec;
};

template<typename T,typename Compare>
void MyQsort<T,Compare>::print()
{
    for(auto &elem : _vec)
    {
        cout << elem << " ";

    }
    cout << endl;
}

template<typename T, typename Compare>
MyQsort<T,Compare>::MyQsort(T *arr, size_t size, Compare com)
{
    for(size_t i=0; i < size; i++)
    {
        _vec.push_back(arr[i]);
    }

    quick(0,_vec.size()-1,com);
}

template<typename T,typename Compare>
void MyQsort<T,Compare>::quick(int left, int right, Compare &com)
{
    int pivot;
    if(left < right)
    {
        pivot = partition(left, right, com);
        quick(left, pivot - 1, com);
        quick(pivot + 1, right, com);
    }

}


template<typename T,typename Compare>
int MyQsort<T,Compare>::partition(int left, int right, Compare &com)
{
    int indexi,indexk;
    for(indexi = left, indexk = left; indexi < right; ++indexi)
    {
        if(com(_vec[indexi], _vec[right]))
        {
            swap(_vec[indexi], _vec[indexk]);
            ++indexk;
        }
    }
    swap(_vec[indexk], _vec[right]);

    return indexk;

}

int main(void)
{
    int arr[10] = {1, 2, 4, 5, 8, 6, 7, 10, 9};
    MyQsort<int> mqInt(arr, 10, std::less<int>());

    mqInt.print();

    return 0;

}
