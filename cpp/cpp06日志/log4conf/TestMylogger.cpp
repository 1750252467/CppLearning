#include"Mylogger.hpp"
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace wd;

void test0()
{
    Mylogger::getInstance()->error(prefix("this is an error message!"));
    Mylogger::getInstance()->warn(prefix("this is an warn message!"));
    Mylogger::getInstance()->info(prefix("this is an info message!"));
    Mylogger::getInstance()->debug(prefix("this is an debug message!"));

    cout<<"Mylogger::Priority::WARN="<<Mylogger::Priority::WARN<<endl;

    cout<<"Mylogger::Priority::ERROR="<<Mylogger::Priority::ERROR<<endl;
    cout<<"Mylogger::Priority::INFO="<<Mylogger::Priority::INFO<<endl;
    cout<<"Mylogger::Priority::DEBUG="<<Mylogger::Priority::DEBUG<<endl;
}

void test1()
{
    cout<<__FILE__<<" "<<__LINE__<<__FUNCTION__<<endl;
}

void test2(){
    LogError("this is a error message!");
    LogWarn("this is a error message!");
    LogInfo("this is a error message!");
    LogDebug("this is a error message");
}

void test(int number,const char *pstr){
    Mylogger::getInstance()->debug(prefix("this is a error message! number = %d,str = %s"),number,pstr);

    LogError("this is a error message! number = %d, str = %s",number,pstr);
    LogWarn("this is a warn messages!");
    LogInfo("this is a info message!");
    LogDebug("this is a error messages!");

}

void initlog4(int number, const char *str){//number 和数字可选填，
    test(number,str);
}
int main(int argc, char **argv)
{
    //第一个输入数字，第二个输入字符串
    test(atoi(argv[1]),argv[2]);
    return 0;
}







