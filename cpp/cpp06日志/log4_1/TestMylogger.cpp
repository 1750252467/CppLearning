#include"Mylogger.hpp"
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using namespace wd;

void test(int number,const char *pstr){
    Mylogger::getInstance()->info(prefix("this is a error message! number = %d,str = %s"),number,pstr);

    //LogError("this is a error message!");
   // LogWarn("this is a warn messages!");
    LogInfo("this is a info message! number = %d, str = %s\n",number,pstr);
    //LogDebug("this is a error messages!");

}

int main(int argc, char **argv)
{
    //第一个输入数字，第二个输入字符串
    test(atoi(argv[1]),argv[2]);
    return 0;
}







