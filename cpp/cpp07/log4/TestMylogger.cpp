#include"Mylogger.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace wd;

void test(){
    int number = 10;
    const char *pstr = "hello,world";
    Mylogger::getInstance()->debug(prefix("this is a error message! number = %d,str = %s"),number,pstr);

    LogError("this is a error message! number = %d, str = %s",number,pstr);
    LogWarn("this is a warn messages!");
    LogInfo("this is a info message!");
    LogDebug("this is a error messages!");

}

int main(void)
{
    test();
    return 0;
}







