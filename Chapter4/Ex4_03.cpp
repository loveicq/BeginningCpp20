#include <iostream>

int main()
{
    std::cout << "请输入一个50-100之间的整数：";

    int value{};
    std::cin >> value;

    if (value)
        std::cout << "你输入的是一个非0数字。" << std::endl;
    if (value < 50)
        std::cout << "输入无效！你输入的数字小于50！" << std::endl;
    if (value > 100)
        std::cout << "输入无效！你输入的数字大于100！" << std::endl;

    std::cout << "你输入的数字是" << value << "。" << std::endl;

    return 0;
}