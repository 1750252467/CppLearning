#include <stdlib.h>
#include <pthread.h>

#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
public:
    static Singleton *getInstance()
    {
        pthread_once(&_once,initRoutine);
        return _pInstance;
    }

    static void destroy()
    {
        cout<<"Singleton::destroy()"<<endl;
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    static void initRoutine()
    {
        _pInstance = new Singleton();
        atexit(destroy);
    }
    void init(int x,int y)
    {
        _x=x;
        _y=y;
    }

    void print()const
    {
        cout<<"_x="<<_x<<" "
            <<"_y="<<_y<<endl;
    }
private:
    Singleton(){cout<<"Singleton()"<<endl;}
    ~Singleton(){cout<<"~Singleton()"<<endl;}
private:
    int _x;
    int _y;
    static Singleton *_pInstance;
    static pthread_once_t  _once;
};

Singleton * Singleton::_pInstance = nullptr;

pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;





void test()
{
    Singleton::getInstance()->init(88,88);
    Singleton::getInstance()->print();
}




int main()
{
    test();
    return 0;
}


