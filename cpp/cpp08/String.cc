#include "String.hh"

String::String()
:_pstr(new char[1]())    
{
    cout<<"String()"<<endl;
}

String::String(const char *pstr)
:_pstr(new char[strlen(pstr)+1])
{
    cout<<"String(const char *pstr)"<<endl;
    strcpy(_pstr,pstr);
}

String::String(const String &rhs)
:_pstr(new char[strlen(rhs._pstr)+1])
{
    cout<<"String(const String &rhs)"<<endl;
    strcpy(_pstr,rhs._pstr);
}


String::~String()
{
    if(_pstr){
        delete [] _pstr;
        _pstr = nullptr;
    }
    cout<<"~String()"<<endl;
}

String &String::operator=(const String &rhs)//防止复制&
{
    if(this != &rhs){
        delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr)+1];
        strcpy(_pstr,rhs._pstr);
    }

    cout<<"String &String::operator=(const String &rhs)"<<endl;
    return *this;
}

String &String::operator=(const char *pstr)
{
    if(_pstr!=pstr){
        delete [] _pstr;
        _pstr = new char[strlen(pstr)+1];
        strcpy(_pstr,pstr);
    }
    cout<<"String &String::operator=(const char *pstr)"<<endl;
    return *this;
}

String &String::operator+=(const String &rhs)
{
    char *tmp = _pstr;//转化成 char*
    _pstr = new char[strlen(tmp)+strlen(rhs._pstr)+1];
    strcpy(_pstr,tmp);
    strcat(_pstr,rhs._pstr);
    delete [] tmp;
    return *this;
}

String &String::operator+=(const char *pstr)
{
    char *tmp = _pstr;//转化成 char*,???
    _pstr = new char[strlen(tmp)+strlen(pstr)+1];
    strcpy(_pstr,tmp);
    strcat(_pstr,pstr);
    delete [] tmp;
    return *this;
}
char &String::operator[](std::size_t index)
{
    if()
    return _pstr[index];
}

void String::print()const
{
    if(_pstr){
        cout<<_pstr<<endl;
    }

}

std::size_t String::size() const
{
    return strlen(_pstr);

}

const char* String::c_str()const
{
    return _pstr;
}



void test0()//测试
{
    String s1="hello";
    s1.print();

    String s2("hhhh");
    s2.print();

    String s3(s2);
    s3.print();
    
    char *str="he";
    String s4(str);
    s4.print();
}

int main(int argc,char** argv)
{
    test0();
    return 0;
}
















