// Ex4_05.cpp
// 使用if-else语句
#include <iostream>
int main()
{
    // std::system("chcp 65001 >nul");

    long number{};
    std::cout << "请输入一个小于20亿的整数:";
    std::cin >> number;

    if (number % 2)
    {
        std::cout << "你输入的是奇数." << std::endl;
    }
    else
    {
        std::cout << "你输入的是偶数." << std::endl;
    }

    // std::system("pause");
}