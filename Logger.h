#ifndef __LOGGER__
#define __LOGGER__

#include "noncopyable.h"

#include <string>


namespace muduo {
    /* 日志级别
    INFO        普通信息
    ERROR       错误信息
    FATAL       崩溃信息
    DEBUG       调试信息
    */
    enum class LogLevel {
        INFO,       
        ERROR,       
        FATAL,      
        DEBUG        
    };

    // 日志类，单例模式
    class Logger  : muduo::noncopyable {
    public:
        // 获取日志类的唯一实例
        static Logger& getInstance();
        // 设置日志级别
        void setLogLevel(LogLevel level);
        // 写日志
        void log(std::string msg);

    private:
        LogLevel m_loglevel;    // 日志级别
        Logger();               // 默认构造
    };
}
#endif 