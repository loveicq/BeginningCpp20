#include <iostream>
#include <format>

int main()
{
    unsigned limit{};

    std::cout << "This program calculates n! and the sum of the integers "
              << "up to n for values 1 to limit.\n";
    std::cout << "What upper limit for n would you like? Input a integer less than 21:";
    std::cin >> limit;

    constexpr auto table_format = "{:>8} {:>8} {:>20}\n";

    std::cout << std::format(table_format, "integer", "sum", "factorial");

    for (unsigned long long n{1}, sum{}, factorial{1}; n <= limit; ++n)
    {
        sum += n;
        factorial *= n;
        std::cout << std::format(table_format, n, sum, factorial);
    }
}