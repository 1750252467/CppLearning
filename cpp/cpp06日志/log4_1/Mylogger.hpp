#ifndef __WD__MYLOGGER_H__
#define __WD__MYLOGGER_H__

#include <log4cpp/Category.hh>

#include <string>
using std::string;

namespace wd
{
class Mylogger
{
public:
    enum Priority{
        ERROR =300,
        WARN,
        INFO,
        DEBUG
    };
    //单例模式
//保证只能创建一个堆对象 ，并通过 类直接调用
    static Mylogger * getInstance();
    static void destory();
   //可变参数模板对函数参数列表的第一项进行处理，再将剩下的内容传递给递归调用，直到传递的函数参数列表为空 

    template <class... Args>
        void warn(const char *msg,Args... args)
        {
            _mycat.warn(msg,args...);
        }

    template <class...Args>
        void  error(const char *msg,Args... args)
        {
            _mycat.warn(msg,args...);
        }

    template <class...Args>
        void  info(const char *msg,Args... args)
        {
            _mycat.info(msg,args...);
        }

    template <class...Args>
        void  debug(const char *msg,Args... args)
        {
            _mycat.warn(msg,args...);
        }

    void warn(const char *msg);
    void error(const char *msg);
    void info(const char *msg);
    void debug(const char *msg);
//设置优先级，进行日志过滤,并保证该类可以间接设置优先级
    void setPriority(Priority p);
private:
    Mylogger();//保证只能创建堆对象
    ~Mylogger();
private:
    log4cpp::Category &_mycat;

    static Mylogger *_pInstance;
};
//宏定义处理日志中的
#define prefix(msg) string("[")\
    .append(__FILE__).append(":")\
    .append(__FUNCTION__).append(":")\
    .append(std::to_string(__LINE__)).append("]")\
    .append(msg).c_str()
#define LogError(msg,...) Mylogger::getInstance()->error(prefix(msg),##__VA_ARGS__)
#define LogWarn(msg,...) Mylogger::getInstance()->warn(prefix(msg),##__VA_ARGS__)
#define LogInfo(msg,...) Mylogger::getInstance()->info(prefix(msg),##__VA_ARGS__)
#define LogDebug(msg,...) Mylogger::getInstance()->debug(prefix(msg),##__VA_ARGS__)




}

#endif


