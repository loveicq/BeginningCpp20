#include <iostream>

int main()
{
    auto k{430u};
    auto j{(k >> 4) & ~(~0u << 3)};
    std::cout << j << std::endl;

    return 0;
}