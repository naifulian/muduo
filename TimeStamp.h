#ifndef __TIME_STAMP__
#define __TIME_STAMP__

#include <cstdint>
#include <string>
#include <ctime>
#include <iostream>

namespace muduo {
    // 时间类
    class TimeStamp {
    public:
        TimeStamp();
        // 不能隐式转换
        explicit TimeStamp(int64_t microSecondsSinceEpoch);
        // 获取从启动到当前时间经过的秒数
        static TimeStamp now();
        // 转换为字符串格式
        std::string toString() const;
    private:
        int64_t m_microSecondsSinceEpoch = 0;
    };                                                                                         
}

#endif 