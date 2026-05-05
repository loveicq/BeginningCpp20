// Ex8_09C.cpp
// 按引用传递数组，std::array<>方式
#include <iostream>
#include <array>

double average10(const std::array<double, 10> &);

int main()
{
    std::array<double, 10> values{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average10(values) << std::endl;
}

double average10(const std::array<double, 10> &array)
{
    double sum{};
    for (auto val : array)
        sum += val;
    return sum / array.size();
}