#include <iostream>
#include <cctype>

int main()
{
    std::cout << "请输入一个字母：";

    char letter;
    std::cin >> letter;

    if (std::isupper(letter))
    {
        std::cout << "你输入的是大写字母。\n";
        return 0;
    }

    if (std::islower(letter))
    {
        std::cout << "你输入的是小写字母。\n";
        return 0;
    }

    std::cout << "你输入的不是字母。\n";

    return 0;
}