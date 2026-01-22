#include <iostream>
#include <array>

int main()
{
    const size_t maxNumber{93};
    std::array<unsigned long long, maxNumber> fibonacci;
    fibonacci[0] = fibonacci[1] = 1UL;
    size_t i{1}; // 下面的while循环选件没有"=",可以使用size_t类型变量
    while (++i < maxNumber)
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];

    std::cout << "The first " << maxNumber << " fibonacci numbers are:\n";
    for (auto number : fibonacci)
        std::cout << number << std::endl;
}