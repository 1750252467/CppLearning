#include<iostream>
#include<string>
#include<regex>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::regex;

class judge
{
public:
    static const regex pattern;

    bool isNumber(string str)
    {
        return regex_match(str,pattern);
    }
};

const regex judge::pattern("[+-]?(?:\\d+\\.?\\d*|\\.\\d+)(?:[Ee][+-]?\\d+)?");

void test1()
{
    string str;
    cin>>str;
    judge s;

    bool b = s.isNumber(str);
    if(b){
        cout<<"this is a number."<<endl;
        cout<<str<<endl;
        return;
    }else{
        cout<<"this is not a number."<<endl;
    }
}

int main(int argc,char **argv)
{
    test1();
    return 0;
}
