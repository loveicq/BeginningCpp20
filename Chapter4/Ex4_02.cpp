#include <iostream>
#include <format>
#include <compare>

int main()
{
    std::cout << "请输入一个整数:";

    int value;
    std::cin >> value;

    std::strong_ordering ordering{value <=> 0};

    std::cout << std::format("value < 0:{}\n", ordering == std::strong_ordering::less);
    std::cout << std::format("value > 0:{}\n", ordering == std::strong_ordering::greater);
    std::cout << std::format("value == 0:{}\n", ordering == std::strong_ordering::equal);

    return 0;
}