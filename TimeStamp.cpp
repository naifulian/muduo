#include "TimeStamp.h"

muduo::TimeStamp::TimeStamp() : m_microSecondsSinceEpoch(0) { }

muduo::TimeStamp::TimeStamp(int64_t microSecondsSinceEpoch) 
    : m_microSecondsSinceEpoch(microSecondsSinceEpoch) { }

muduo::TimeStamp muduo::TimeStamp::now() {
    return muduo::TimeStamp(time(nullptr));
}

std::string muduo::TimeStamp::toString() const {
    char buf[128] = {0};
    tm *tm_time = localtime(&m_microSecondsSinceEpoch);
    snprintf(buf, 128, "%4d-%02d-%02d %02d:%02d:%02d",
             tm_time->tm_year + 1900,
             tm_time->tm_mon + 1,
             tm_time->tm_mday,
             tm_time->tm_hour,
             tm_time->tm_min,
             tm_time->tm_sec);
    return buf;
}