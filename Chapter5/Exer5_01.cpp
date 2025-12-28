#include <iostream>

int main()
{
    auto i{1};
    auto value1{1};
    auto value2{1};
    auto value3{1};

    std::cout << "运算结果是:" << (value1 += ++i, value2 += ++i, value3 += ++i) << std::endl;
}