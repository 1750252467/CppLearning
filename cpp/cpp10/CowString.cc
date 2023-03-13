#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class CowString
{
public:
    class CharProxy
    {
    public:
        CharProxy(CowString & self,size_t idx);
        //重载s[0]="s"
        char & operator=(const char &ch);
        //重载s[0]
        operator char()
        {
           // cout<<"operator char()"<<endl;
            return _self._pstr[_idx];
        }
    private:
        CowString & _self;
        size_t _idx;

    };
public:
    CowString()
    :_pstr(calloc())
    {
        init_use_count();
    }

    CowString(const char *pstr)
    :_pstr(calloc(pstr))
    {
        init_use_count();
        strcpy(_pstr,pstr);
    }

    CowString(const CowString &rhs)
    :_pstr(rhs._pstr)
    {
        increase();

    }

    ~CowString(){ release(); }

    void release()
    {
        decrease();
        if(use_count()==0){
            delete [] (_pstr - refCountCapacity);
            cout<<"free heap space"<<endl;
        }
    }

    CowString & operator=(const CowString & rhs)
    {
        if(this !=&rhs){
            release();
            _pstr = rhs._pstr;
            increase();
        }
        return *this;
    }
    //重载s[0]入口
    CharProxy operator[](size_t idx)
    { return CharProxy(*this,idx); }

    size_t length()const{return strlen(_pstr);}

    int use_count()const
    {
        return *reinterpret_cast<int*>(_pstr-refCountCapacity);
    }

private:
    void init_use_count()
    { *reinterpret_cast<int*>(_pstr - refCountCapacity)=1; }

    void increase()
    { ++*reinterpret_cast<int*>(_pstr - refCountCapacity);  }

    void decrease()
    { --*reinterpret_cast<int*>(_pstr- refCountCapacity); }

    char *calloc(const char *pstr = nullptr)
    {
        if(pstr){
            return new char[strlen(pstr)+refCountCapacity+1]()+refCountCapacity;
        }else{
            return new char[refCountCapacity+1]() +refCountCapacity;
        }
    }

    friend std::ostream &operator<<(std::ostream &os,const CowString & rhs);
private:
    char *_pstr;
    static const int refCountCapacity = 4;

};

std::ostream& operator<<(std::ostream & os,const CowString &rhs)
{
    os<<rhs._pstr;
    return os;
}

CowString::CharProxy::CharProxy(CowString & self,size_t idx)
:_self(self)
,_idx(idx)
{}


char & CowString::CharProxy::operator=(const char &ch)
{
    if(_idx<_self.length()){
        if(_self.use_count()>1){
            _self.decrease();
            char *ptmp = _self.calloc(_self._pstr);
            strcpy(ptmp,_self._pstr);
            _self._pstr = ptmp;
            _self.init_use_count();
        }
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    }else{
        static char nullchar = '\0';
        return nullchar;

    }
}


void test()
{
    CowString str1("hello,naxida");
    CowString str2("hello,naxida");
    CowString str3=str1;
    CowString str4=str3;
    //读操作
    cout<<"str1="<<str1<<"  str1.use_count:"<<str1.use_count()<<endl;
    cout<<"str2="<<str2<<"  str2.use_count:"<<str2.use_count()<<endl;
    cout<<"str3="<<str3<<"  str3.use_count:"<<str3.use_count()<<endl;
    cout<<"str4="<<str4<<"  str4.use_count:"<<str4.use_count()<<endl;
    cout<<"读操作：str1[3]="<<str1[3]<<endl;
    cout<<endl; 

    cout<<"str1="<<str1<<"  str1.use_count:"<<str1.use_count()<<endl;
    cout<<"str2="<<str2<<"  str2.use_count:"<<str2.use_count()<<endl;
    cout<<"str3="<<str3<<"  str3.use_count:"<<str3.use_count()<<endl;
    cout<<"str4="<<str4<<"  str4.use_count:"<<str4.use_count()<<endl;
    //写操作
    cout<<endl;
    cout<<"修改前str1="<<str1<<endl;
    str1[3] = '*';
    cout<<"str1[3]="<<str1[3]<<endl;
    cout<<"修改后str1="<<str1<<endl;
    
    cout<<endl;
    cout<<"str1="<<str1<<"  str1.use_count:"<<str1.use_count()<<endl;
    cout<<"str2="<<str2<<"  str2.use_count:"<<str2.use_count()<<endl;
    cout<<"str3="<<str3<<"  str3.use_count:"<<str3.use_count()<<endl;
    cout<<"str4="<<str4<<"  str4.use_count:"<<str4.use_count()<<endl;
}


int main(){
    test();
    return 0;
}
