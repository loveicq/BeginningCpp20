// Ex5_12.cpp
#include <iostream>
#include <format>

int main()
{
    size_t count{};
    std::cout << "How man height will you enter? ";
    std::cin >> count;
    int height[count];

    size_t entered{};
    while (entered < count)
    {
        std::cout << "Enter a height (in inches): ";
        std::cin >> height[entered];
        if (height[entered] > 0)
        {
            ++entered;
        }
        else
        {
            std::cout << "A height must be positive - try again.\n";
        }

        unsigned total{};
        for (size_t i{}; i < count; ++i)
        {
            total += height[i];
        }

        std::cout << std::format("The average height is {:.1f}\n",
                                 static_cast<double>(total) / count);
    }
}