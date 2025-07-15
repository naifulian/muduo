#include <iostream>

#include "Logger.h"
#include "TimeStamp.h"
/*
- LOG_INFO 等宏能不能优化
- 使用 MUDUO_DEBUG 宏控制 DEBUG 日志信息的输出，考虑使用配置文件
*/

#define LOG_INFO(logMsgFormat, ...)                   \
    do {                                              \
        mudo::Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(INFO);                     \
        char buf[1024] = {0};                         \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf) \
    } while (0);

#define LOG_ERROR(logMsgFormat, ...)                   \
    do {                                              \
        mudo::Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(ERROR);                     \
        char buf[1024] = {0};                         \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf) \
    } while (0);

#define LOG_FATAL(logMsgFormat, ...)                   \
    do {                                              \
        mudo::Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(FATAL);                     \
        char buf[1024] = {0};                         \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf) \
    } while (0);

#ifdef MUDUO_DEBUG
#define LOG_DEBUG(logMsgFormat, ...)                   \
    do {                                              \
        mudo::Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(DEBUG);                     \
        char buf[1024] = {0};                         \
        snprintf(buf, 1024, logMsgFormat, ##__VA_ARGS__); \
        logger.log(buf) \
    } while (0);
#endif

muduo::Logger& muduo::Logger::getInstance() {
    // 这种写法还是线程安全的
    static Logger logger;
    return logger;
}

void muduo::Logger::setLogLevel(LogLevel level) {
    m_loglevel = level;
}

// [日志级别] time: msg
void muduo::Logger::log(std::string msg) {
    switch(m_loglevel) {
        case LogLevel::INFO:
            std::cout << "[INFO]";
            break;
        case LogLevel::FATAL:
            std::cout << "[FATAL]";
            break;
        case LogLevel::ERROR:
            std::cout << "[ERROR]";
            break;
        case LogLevel::DEBUG:
            std::cout << "[DEBUG]";
            break;
        default:
            break;
        }

    std::cout << muduo::TimeStamp::now().toString() << ": " << msg << std::endl;
}