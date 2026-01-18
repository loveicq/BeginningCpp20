#include <iostream>

int main()
{
    const int maxCharacters{1000};
    char characters[maxCharacters]{};

    std::cout << "Please input a string:\n";

    // 采用循环直接将字符写入数组.包含空白字符,所以得用cin.get()
    char character{};
    int count{};
    do
    {
        std::cin.get(character);
        if (character == '\n')
            break;
        characters[count] = character;
        ++count;
    } while (character != '\n' && count < maxCharacters);

    if (count == 0)
    {
        std::cout << "No characters were entered!\n";
        return 1;
    }

    // 显示字符总数
    std::cout << "You entered " << count << " characters.\n";

    // 逆向输出字符串
    std::cout << "Reverse output this string:";
    for (; count >= 0; --count)
        std::cout << characters[count];
    std::cout << ".\n";
}