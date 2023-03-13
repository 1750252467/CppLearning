#include <iostream>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;
using std::copy;
using std::uninitialized_copy;

template<typename T>
class Vector
{
public:
    typedef T *iterator;

    Vector()
    :_start(nullptr)
     ,_finish(nullptr)
     ,_end_of_storage(nullptr)
    {}
    ~Vector();
    
    iterator begin()
    {
        return _start;
    }

    iterator end()
    {
        return _finish;
    }

    void push_back(const T&);
    void pop_back();

    int size() const;
    int capacity()const;


private:
    void reallocate();
private:
    static std::allocator<T> _alloc;

    T *_start;
    T *_finish;
    T *_end_of_storage;
};

template <typename T>
std::allocator<T> Vector<T>::_alloc;

template <typename T>
Vector<T>::~Vector()
{
    if(_start)
    {
        while(_finish != _start)
        {
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start,capacity());
    }
}

template <typename T>
void Vector<T>::pop_back()
{
    if(size() > 0){
        _alloc.destroy(--_finish);
    }
}

template <typename T>
int Vector<T>::size() const
{
    return _finish - _start;
}

template <typename T>
int Vector<T>::capacity() const
{
    _end_of_storage - _start;
}

template <typename T>
void Vector<T>::reallocate()
{
    int oldCapacity = capacity();
    int newCapacity = 2* oldCapacity > 0 ? 2 *oldCapacity : 1;
    
    T *tmp = _alloc.allocate(newCapacity);
    if(_start)
    {
        uninitialized_copy(_start, _finish, tmp);

        while(_finish != _start)
        {
            _alloc.destroy(--_finish);
        }

        _alloc.deallocate(_start,oldCapacity);
    }

    _start = tmp;
    _finish = tmp + oldCapacity;
    _end_of_storage = tmp + newCapacity;
}

template <typename Container>
void display(const Container &con)
{
    cout << "con.size()" << con.size() << endl;
    cout << "con.capacity()" << con.capacity() << endl;
}

void test()
{
    Vector<int> number;
    display(number);

    cout << endl;
       number.push_back(1);
    display(number);

    cout << endl;
    number.push_back(2);
    display(number);

    cout << endl;
    number.push_back(3);
    display(number);

    cout << endl;
    number.push_back(4);
    display(number);

    cout << endl;
    number.push_back(5);
    display(number);

    for(auto &elem : number)
    {
        cout << elem << "  ";
    }
    cout << endl;
}


int main(void)
{
    test();
    return 0;
}














