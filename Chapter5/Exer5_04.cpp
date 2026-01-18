#include <iostream>

int main()
{
    const unsigned maxCharacters{1000};
    char enterString[maxCharacters]{}; // 无{}初始化，数组会存入垃圾值，直接使用会导致程序异常，比如后面无cin.getline()的操作。数组在全局/静态作用域（函数外或带 static 关键字）例外。
    std::cout << "Enter a string less or equal than 1000 characters:" << std::endl;
    std::cin.getline(enterString, maxCharacters);

    // 统计字符串包含的字符数量
    size_t count{};
    for (; enterString[count]; ++count)
    {
    }

    // 如果未输入字符,则提示未输入字符,直接退出程序
    if (count == 0)
    {
        std::cout << "No characters were entered.\n";
        return 1;
    }

    // 如果已输入字符,则显示字符总数
    std::cout << "There're " << count << " characters.\n\n";

    // 反向输出字符串
    std::cout << "Reverse output this string:";
    while (count > 0)
    {
        std::cout << enterString[count - 1];
        count--;
    }
    std::cout << "." << std::endl;
}