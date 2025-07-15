# 1.noncopyable 类

muduo 中有一个特殊的基类 noncopyable，这个类可以使得它的派生类不能被拷贝构造和赋值，这样做的好处是利用继承复用代码
```cpp
// noncopyable 被子类继承后，派生类对象可以正常的构造和析构，但是不能拷贝构造、使用复制运算符
// 派生类对象的构造会调用基类对应的的构造函数，将基类的拷贝构造删除掉
class noncopyable {
public:
	// 删除拷贝构造
	noncopyable(const noncopyable &other) = delete;
	// 删除赋值运算符
	noncopyable &operator=(const noncopyable &other) = delete;
	 
protected:
	noncopyable() = default;
	~noncopyable() = default;
};
```
# 2.TimeStamp 类

TimeStamp 类用于在日志类中打印时间，提供
- 构造函数
	- 默认构造函数
	- 参数为 int64_t 的构造函数，该构造函数不能发生隐式转换
- 两个接口 now 和 toString
- 使用的方式如下,比如打印当前时间
```cpp
std::cout << muduo::TimeStamp::now().toString() << std::endl;
```

具体实现使用的 ctime 库的 time 函数和 localtime 函数，后面可以使用 c++ 的标准库 chrnon 库替换

```cpp
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
```
- 测试
```cpp
// test_time.cpp
#include "TimeStamp.h"

#include <iostream>

int main() {
    std::cout << muduo::TimeStamp::now().toString() << std::endl;
    return 0;
}
```

# Logger 类

使用一个枚举类 LogLevel 表示日志的四种级别：INFO、ERROR、FATAL、DEBUG
```cpp
enum class LogLevel {
	INFO,       
	ERROR,       
	FATAL,      
	DEBUG        
};
```


类 Loggger 继承自 noncopybale，不能拷贝构造和赋值，使用的是单例模式
```cpp
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
```

在 Logger 中提示用四个宏函数实现，这种实现方式应该不太好，后面想办法换掉
```cpp
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
```

一般来说，DEBUG 模式输出的信息最多，这里使用条件编译，使用宏 MUDUO_DEBUG 来控制是否能使用 DEBUG 级别

# 4.运行

1. 指定构建目录为 build，源码目录为当前目录
```bash
cmake -B build -S .
```

2. 编译项目
```bash
cmake --build build
```

