// Ex9_04.cpp
// 使用span<T,N>替代T(&)[N]
#include <iostream>

double average10(std::span<double, 10> values);

int main()
{
    double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average10(values) << std::endl;
}

double average10(std::span<double, 10> values)
{
    double sum{};
    for (auto value : values)
        sum += value;
    return sum / 10;
}