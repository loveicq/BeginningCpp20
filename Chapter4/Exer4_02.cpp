#include <iostream>
#include <format>

int main()
{
    int a{}, b{};

    std::cout << "输入整数a:";
    std::cin >> a;
    std::cout << "输入整数b:";
    std::cin >> b;

    if (a <= 0 || b <= 0)
    {
        std::cout << "a和b必须是正整数!" << std::endl;
        return 1;
    }

    if (a < b)
    {
        if (b % a == 0)
            std::cout << std::format("{}是{}的整数倍.\n", b, a);
        else
            std::cout << std::format("{}不是{}的整数倍.\n", b, a);
    }
    else
    {
        if (a % b == 0)
            std::cout << std::format("{}是{}的整数倍.\n", a, b);
        else
            std::cout << std::format("{}不是{}的整数倍.\n", a, b);
    }
}