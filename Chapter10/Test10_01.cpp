// Text10_01.cpp
// 非类型的模板参数
#include <iostream>

template <typename T, int lower, int upper>
bool is_in_range(const T& value) {
    return value >= lower && value <= upper;
}

int main() {
    double value{200.0};
    // std::cout<<is_in_range(value)<<std::endl;//无法编译，因为少了参数
    std::cout << is_in_range<double, 0, 100>(value) << std::endl;  // OK!
    //<double, 0,
    // 100>是模板参数列表，必须是编译期常量，(value)是函数参数列表，可以运行时提供

    // int i{5};//不是常量，不能编译
    const int i{5};  // 有const，是常量，可以编译
    std::cout << is_in_range<double, i, i * 100>(value) << std::endl;
}