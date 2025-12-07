#include <iostream>

int main()
{
    char first{};
    char second{};

    std::cout << "请输入一个字符:";
    std::cin >> first;
    std::cout << "请输入第二个字符:";
    std::cin >> second;

    std::cout << std::boolalpha; // 设置bool值显示为true和false,而非1和0。

    std::cout << "表达式 '" << first << " < " << second << "' 的值为"
              << (first < second) << "." << std::endl;
    std::cout << "表达式 '" << first << " == " << second << "'的值为 "
              << (first == second) << "." << std::endl;

    std::cout << std::noboolalpha; // 设置bool值显示为1和0,而非true和false。

    /*
    使用下面的语句更简洁,还避免了运算符优先级的困扰:
    std::cout << std::format("表达式 '{} < {}' 的值为{}.\n", first, second, first < second);
    std::cout << std::format("表达式 '{} == {}' 的值为{}.\n", first, second, first == second);
    */

    return 0;
}