#include <iostream>
#include <format>

int main()
{
    unsigned input{};

    std::cout << "Input a positive integer: ";
    std::cin >> input;

    size_t perLine{};
    for (size_t i{1}; i <= input; ++i)
    {
        if (i % 2 != 0)
        {
            std::cout << std::format("{:<10}", i * i);
            perLine += 1;
            if (perLine == 10)
            {
                std::cout << std::endl;
                perLine = 0;
            }
        }
    }

    std::cout << std::endl;
}