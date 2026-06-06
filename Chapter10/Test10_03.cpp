// Test10_03.cpp
// 测试缩写的函数模板
#include <iostream>

auto sqrt(auto x) { return x * x; } // 省略template和typename关键字

int main() { std::cout << "Sqrt(1.5) = " << sqrt(1.5) << std::endl; }