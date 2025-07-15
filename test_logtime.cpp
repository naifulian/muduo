#include "TimeStamp.h"

#include <iostream>

int main() {
    std::cout << muduo::TimeStamp::now().toString() << std::endl;
    return 0;
}