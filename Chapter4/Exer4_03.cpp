#include <iostream>

int main()
{
    double num{};

    std::cout << "请输入一个1-100之间的数字: ";
    std::cin >> num;

    if (num < 1 || num > 100)
    {
        std::cout << "数值不在1-100范围内." << std::endl;
        return 1;
    }

    if (num > 50)
    {
        std::cout << "数字大于50" << std::endl;
    }
    else if (num < 50)
    {
        std::cout << "数字小于50" << std::endl;
    }
    else
    {
        std::cout << "数字等于50" << std::endl;
    }
}