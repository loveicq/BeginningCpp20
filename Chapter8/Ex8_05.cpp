// Ex8_05.cpp
// 将数组传递给函数
#include <iostream>
#include <array> //用于 std::size()

double average(double array[], size_t count); // 函数原型

int main()
{
    double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average(values, std::size(values)) << std::endl;
}

// 计算平均值的函数
double average(double* array, size_t count)
{
    double sum{}; // 在此累加总和
    for (size_t i{}; i < count; ++i)
        sum += *array++; // 对数组元素求和
    return sum / count;  // 返回平均值
}