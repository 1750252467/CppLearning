#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout<<"AutoRelease()"<<endl;

        }

        ~AutoRelease()
        {
            cout<<"~AutoRelease()"<<endl;
            if(_pInstance){
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

public:
    static Singleton *getInstance()
    {
        if(nullptr==_pInstance){
            _pInstance =new Singleton();
        }
        return _pInstance;
    }

    void init(int ix,int iy)
    {
        _ix=ix;
        _iy=iy;

    }

    void print() const
    {
        cout<<"_ix"<<_ix<<","
            <<"_iy"<<_iy<<endl;
    }

private:
    Singleton(){cout<<"Singleton()"<<endl;}
    ~Singleton(){
        cout<<"~Singleton()"<<endl;
    }
private:
    int _ix;
    int _iy;
    static Singleton *_pInstance;
    static AutoRelease _ar;
};


Singleton *Singleton::_pInstance = nullptr;

Singleton::AutoRelease Singleton::_ar;



void test0()
{
    Singleton::getInstance()->init(1,2);
    Singleton::getInstance()->print();

}

int main(void){
    test0();
    return 0;
}





