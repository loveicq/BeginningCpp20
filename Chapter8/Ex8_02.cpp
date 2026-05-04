// Ex8_02.cpp
// 计算幂，重新构建。编译此程序会报错，因为函数声明在调用之后
#include <iostream>
#include <format>

int main()
{
    for (int i{-3}; i <= 3; ++i)
    {
        std::cout << std::format("{:10g}", power(8.0, i));
    }

    std::cout << std::endl;
}

double power(double x, int n)
{
    double result{1};

    if (n == 0)
        return 1;
    if (n > 0)
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