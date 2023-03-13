#include <math.h>
#include <iostream>
#include <vector>
#include <ostream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;


template<typename T>
void swap(T &lhs, T &rhs)
{
    auto temp = lhs;
    lhs = rhs;
    rhs = temp;
}

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size,Compare);
    void heapAdjust(size_t ,size_t ,Compare&);
    void sort(Compare&);
    void print();

private:
    vector<T> vec;
};

template <typename T, typename Compare>
void HeapSort<T,Compare>::print()
{
    for(auto &elem : vec)
    {
        cout<< elem << "  ";
    }
    cout << endl;
}

template <typename T, typename Compare >
void HeapSort<T, Compare>::heapAdjust(size_t adjustpos, size_t arrlen, Compare& com)
{

    size_t dad = adjustpos;
    size_t son= 2 * dad + 1;
    while(son < arrlen)
    {
        if(son + 1 < arrlen && com(vec[son],vec[son + 1]))
        {
            ++son;
        }
        if(com(vec[dad], vec[son]))
        {
            swap(vec[dad], vec[son]);
            dad = son;
            son= 2 * dad + 1;
        }
        else
        {
            break;
        }
    }
}

template <typename T, typename Compare >
HeapSort<T, Compare>::HeapSort(T *arr, size_t size, Compare com)
{
    for (size_t i = 0; i < size; i++)
    {
        vec.push_back(arr[i]);

    }
    for (int i = size/2 - 1; i >= 0; i--)
    {
        heapAdjust(i, size,com);

    }
    swap(arr[0], arr[size - 1]);
    sort(com);

}

template <typename T, typename Compare >
void HeapSort<T, Compare>::sort(Compare& com)
{
    size_t size = vec.size();
    for (size_t i = size; i > 1; i--)
    {
        heapAdjust(0, i, com);
        swap(vec[0], vec[i - 1]);
    }
}

int main(int argc, char **argv)
{
    int arr[10] = {1, 2, 6, 3, 4, 8, 5, 7, 9, 10};
    HeapSort<int> hs(arr, 10, std::less<int>());
    hs.print();
    cout << endl;
    return 0;
}

