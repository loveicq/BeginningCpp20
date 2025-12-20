#include <iostream>

int main()
{
    int a{}, b{};

    std::cout << "输入整数a:";
    std::cin >> a;
    std::cout << "输入整数b:";
    std::cin >> b;

    if (a == b)
        std::cout << "a等于b" << std::endl;
    else
        std::cout << "a不等于b" << std::endl;
}