#include <iostream>

int main()
{
    std::cout << "请输入一个字母:";

    char letter{};
    std::cin >> letter;

    if (letter >= 'A')
    {
        if (letter <= 'Z')
        {
            std::cout << "你输入的是大写字母。\n";
            return 0;
        }
    }

    if (letter >= 'a') // 此处少一对花括号，也是可以的。
        if (letter <= 'z')
        {
            std::cout << "你输入的是小写字母。\n";
            return 0;
        }

    std::cout << "你输入的不是字母。\n";

    return 0;
}