// Ex8_01.cpp
// 计算幂函数
#include <iostream>
#include <format>

double power(double x, int n)
{
    double result{1};

    if (n >= 0)
    {
        for (int i{1}; i <= n; ++i)
            result *= x;
    }
    else
    {
        for (int i{1}; i <= -n; ++i)
            result /= x;
    }

    return result;
}

int main()
{
    for (int i{-3}; i <= 3; ++i)
        std::cout << std::format("{:10g}", power(8.0, i));

    std::cout << std::endl;
}