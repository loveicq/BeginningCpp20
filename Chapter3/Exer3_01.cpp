#include <iostream>
#include <format>

int main()
{
    int originalInteger{};
    std::cout << "请输入一个整数:";
    std::cin >> originalInteger;
    const auto NOTInteger{static_cast<unsigned>(~originalInteger)};
    std::cout << std::format("{:#034b}|{:#034b}|{:#034b}\n",
                             originalInteger, NOTInteger,
                             NOTInteger + 1);
    std::cout << std::format("{:^34}|{:^34}|{:^34}\n",
                             originalInteger, ~originalInteger, ~originalInteger + 1);

    return 0;
}