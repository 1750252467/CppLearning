#include <stdlib.h>

#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(nullptr==_pInstance){
            atexit(destroy);
            _pInstance = new Singleton();
        }
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
};




Singleton* Singleton::_pInstance= nullptr; 

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


