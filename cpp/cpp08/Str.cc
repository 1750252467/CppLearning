 #include "String.hh"     
 
 String::String()
 : _pstr(new char[1])
 { cout << "String()" << endl; }
     
 String::String(const char *pstr)
 : _pstr(new char[strlen(pstr) + 1]())
 {
     cout << "String(const char*)" << endl;
     strcpy(_pstr, pstr);
 }   
 
 String::String(const String &s)
 : _pstr(new char[strlen(s._pstr) + 1]())
 {
     cout << "String(const String&)" << endl;
     strcpy(_pstr, s._pstr);
 }
 
 String::~String()
 {
     cout << "~String()" << endl;
     if (_pstr) {
         delete [] _pstr;
         _pstr = nullptr;
     }
 }
     
 String& String::operator=(const String &s)
 {
     if (this != &s) {
         delete [] _pstr;
         _pstr = new char[strlen(s._pstr) + 1];
         strcpy(_pstr, s._pstr);
     }
     return *this;
 }
 
 String& String::operator=(const char *pstr)
 {   
     if(_pstr != pstr) {
         delete [] _pstr;
         _pstr = new char[strlen(pstr) + 1];
         strcpy(_pstr, pstr);
     }
     return *this;
 }
 
 String& String::operator+=(const String &s)
 {
     char *tmp = _pstr;
     _pstr = new char[strlen(tmp) + strlen(s._pstr) + 1];
     strcpy(_pstr, tmp);
     strcat(_pstr, s._pstr);
     delete [] tmp;
     return *this;
 }
 
 String& String::operator+=(const char *pstr)
 {
     char *tmp = _pstr;
     _pstr = new char[strlen(tmp) + strlen(pstr) + 1];
     strcpy(_pstr, tmp);
     strcat(_pstr, pstr);
     delete [] tmp;
     return *this;
 }
 
 char& String::operator[](std::size_t index)
 {
     return _pstr[index];
 }
 
 const char& String::operator[](std::size_t index) const
 {
     return _pstr[index];
 }
 
 std::size_t String::size() const
 {
     return strlen(_pstr);
 }
 
 const char* String::c_str() const
 {
     return _pstr;
 }
 
 bool operator==(const String &ls, const String &rs)
 {
     return strcmp(ls._pstr, rs._pstr) == 0;
 }
 
 bool operator!=(const String &ls, const String &rs)
 {
     return strcmp(ls._pstr, rs._pstr) != 0;
 }
 
 
 bool operator<(const String &ls, const String &rs)
 {
     return strcmp(ls._pstr, rs._pstr) < 0;
 }
 
 bool operator>(const String &ls, const String &rs)
 {
     return strcmp(ls._pstr, rs._pstr) > 0;
 }
 
 bool operator<=(const String &ls, const String &rs)
 {
     return strcmp(ls._pstr, rs._pstr) <= 0;
 }
 
 bool operator>=(const String &ls, const String &rs)
 {
     return strcmp(ls._pstr, rs._pstr) >= 0;
 }
 
 std::ostream &operator<<(std::ostream &os, const String &s)
 {
     os << s._pstr;
     return os;
 }
 
 std::istream &operator>>(std::istream &is, String &s)
 {
     is >> s._pstr;
     return is;
 }
 
 String operator+(const String &ls, const String &rs)
 {
     String tmp = ls;
     return tmp += rs;
 }
 
 String operator+(const String &s, const char *pstr)
 {
     String tmp = pstr;
     return tmp += s;
 }
 
 String operator+(const char *pstr, const String &s)
 {
     String tmp = pstr;
     return tmp += s;
 }

void test()
{
    String s1,s2,s3,s4,s5;

    cout<<s1.c_str()<<endl;

}

int main(void)
{
    test();
    return 0;
}








