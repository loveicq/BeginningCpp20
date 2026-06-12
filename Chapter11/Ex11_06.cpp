// Ex11_06.cpp
// Defining and using a namespace
#include <iostream>
#include <numbers>

namespace math
{
const double sqrt2{1.414213562373095}; // the square root of 2
auto square(const auto &x) { return x * x; }
auto pow4(const auto &x)
{
    return square(square(x));
} // 这里square就在本名称空间内，不需要"math::"限定
} // namespace math

int main()
{
    std::cout << "math::sqrt2 has the value " << math::sqrt2 << std::endl;
    std::cout << "This should be 0: " << (math::sqrt2 - std::numbers::sqrt2)
              << std::endl;
    std::cout << "This should be 2: " << math::square(math::sqrt2) << std::endl;
    std::cout << "pow4(math::sqrt2) = " << math::pow4(math::sqrt2)
              << std::endl; // 这里pow4与sqrt2不在名称空间内，必须要"math::"限定
}
