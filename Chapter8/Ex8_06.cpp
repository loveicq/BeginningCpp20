// Ex8_06.cpp
// 将二维数组传递给函数
#include <iostream>
#include <array> //用于 std::size()

double yield(const double values[][4], size_t n);

int main()
{
    double beans[3][4]{{1.0, 2.0, 3.0, 4.0},
                       {5.0, 6.0, 7.0, 8.0},
                       {9.0, 10.0, 11.0, 12.0}};
    std::cout << "Yield= " << yield(beans, std::size(beans)) // std::size(beans)实际得出数组的行数（第一维数量）
              << std::endl;
}

// 计算总产量的函数
double yield(const double array[][4], size_t size)
{
    double sum{};
    for (size_t i{}; i < size; ++i) // 遍历行
        for (double val : array[i]) // 遍历行中的各元素
            sum += val;
    return sum;
}