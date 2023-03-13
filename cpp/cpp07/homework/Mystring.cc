#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String
{
public:
    String()
        :_pstr(new char[1]())
    {
        cout<<"String()"<<endl;
    }

    String(const char *pstr)
        :_pstr(new char[strlen(pstr)+1]())//没有括号将不会初始化
    {
        cout<<"String(const char*)"<<endl;
    }

    String(const String &rhs)
        :_pstr(new char[strlen(rhs._pstr)+1]())
    {
        cout<<"String(const char*)"<<endl;
        strcpy(_pstr,rhs._pstr);
    }

    String &operator=(const String &rhs)
    {
        if(this !=&rhs){
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }

    ~String()
    {
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
        }
        cout<<"~String()"<<endl;
    }

    void print()
    {
        if(_pstr){
            cout<<_pstr<<endl;
        }

    }

    size_t length() const
    {
        return strlen(_pstr);

    }

    const char * c_str() const
    {
        return _pstr;
    }
private:
    char * _pstr;
};

void test0()
{
    String s1;
    s1.print();

    String s2 = "hello,world";
    s2.print();
}

int main()
{
    test0();
    return 0;
}
