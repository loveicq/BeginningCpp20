#include <iostream>
#include <format>
#include <numbers>

int main()
{
    const size_t values_per_line{3};
    size_t values_current_line{};

    for (double radius = 0.2; radius < 3.0 + 0.001; radius += 0.2)
    {
        const auto area = std::numbers::pi * radius * radius;
        std::cout << std::format("radius = {:4.2f}, area = {:5.2f}; ", radius, area);
        if (++values_current_line == values_per_line)
        {
            std::cout << std::endl;
            values_current_line = 0;
        }
    }
    std::cout << std::endl;
}