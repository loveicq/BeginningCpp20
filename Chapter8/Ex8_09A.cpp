// Ex8_09A.cpp
// 按引用传递数组
#include <iostream>
#include <iterator>

double average10(const double (&array)[10]);

int main()
{
    double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average10(values) << std::endl;
}

double average10(const double (&array)[10])
{
    double sum{};
    for (size_t i{}; i < std::size(array); ++i)
        sum += array[i];
    return sum / std::size(array);
}
