// 本程序测试2.9.3节无限大、无限小数值和0的运算结果
#include <iostream>
int main()
{
    double a{1.5}, b{}, c{};
    double result{a / b};
    std::cout << a << "/" << b << "=" << result << std::endl;
    std::cout << result << "+" << a << "=" << result + a << std::endl;
    result = b / c;
    std::cout << b << "/" << c << "=" << result << std::endl;

    return 0;
}