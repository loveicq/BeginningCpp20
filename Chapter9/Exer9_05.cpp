/*************************第9章_练习_第5题************************
为Ex8_09A、Ex8_09B、Ex8_09C编写另外一个版本，这次让average10()函数
使用本章介绍的词汇类型。证明能够对大小固定的C风格数组和std::array<>
容器调用该函数，并且只能对包含10个元素的数组调用。
*****************************************************************/
#include <iostream>
#include <span>
#include <array>

double average10(std::span<const double, 10> data);

int main()
{
    double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::array<double, 10> data{11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
    // double values3[]{1.0, 2.0, 3.0};
    std::cout << "Average_values = " << average10(values) << std::endl;
    std::cout << "Average_data = " << average10(data) << std::endl;
    // std::cout << "Average_value3 = " << average10(values3) << std::endl;
    //不存在从 "double [3]" 转换到 "std::span<const double, 10ULL>" 的适当构造函数
}

double average10(std::span<const double, 10> data)
{
    double sum{};
    for (auto value : data)
        sum += value;

    return sum / data.size();
}