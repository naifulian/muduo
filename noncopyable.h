#ifndef __NONCOPYABLE__
#define __NONCOPYABLE__

namespace muduo {
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
}
#endif 