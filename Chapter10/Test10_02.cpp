// Test10_02.cpp
// 非类型模板参数的最佳做法
#include <iostream>

template <auto lower, auto upper, typename T>
bool is_in_range(const T& value) {
    return value >= lower && value <= upper;
}

int main() {
    double value{100.0};
    std::cout << is_in_range<0, 50>(value)
              << std::endl;  // 类型T可以通过value推断出来
}