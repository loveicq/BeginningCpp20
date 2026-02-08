// Exer6_02.cpp
#include <iostream>
#include <format>
#include <string>

int main()
{
    const size_t NUMBER{50};
    unsigned oddNumbers[NUMBER]{};

    for (size_t i{}; i < NUMBER; ++i)
        oddNumbers[i] = 2 * i + 1;

    unsigned maxValue{*(oddNumbers + NUMBER - 1)};
    size_t width(std::to_string(maxValue).length() + 1);

    size_t count{};
    size_t perLine{10};
    auto *ascendingOrder{oddNumbers};
    std::cout << "正序输出前" << NUMBER << "位正奇数:\n";
    do
    {
        std::cout << std::format("{:{}}", *(ascendingOrder++), width);
        if ((count + 1) % perLine == 0)
            std::cout << std::endl;
    } while (++count < NUMBER);

    ascendingOrder = oddNumbers + NUMBER - 1;
    count = 0;
    std::cout << "\n逆序输出前" << NUMBER << "位正奇数:\n";
    while (true)
    {
        std::cout << std::format("{:{}}", *(ascendingOrder--), width);
        if (++count % perLine == 0)
            std::cout << std::endl;
        if (count == NUMBER)
            break;
    }
}