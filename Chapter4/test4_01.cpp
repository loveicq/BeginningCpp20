#include <iostream>
#include <cctype>

int main()
{
    system("chcp 65001 >nul");

    char letter{};

    std::cout << "请输入一个字符:";
    std::cin >> letter;

    if (std::isalnum(letter))
    {
        std::cout << "这是一个字母或数字." << std::endl;
    }
    else
    {
        std::cout << "这既不是字母也不是数字." << std::endl;
    }

    system("pause");

    return 0;
}