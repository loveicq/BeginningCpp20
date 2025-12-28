#include <iostream>
#include <format>

int main()
{
    unsigned limit{};

    std::cout << "This program calculates n! and the sum of the integers "
              << "up to n for values 1 to limit.\n";
    std::cout << "What upper limit for n would you like? Input a ingeter less than 21: ";
    std::cin >> limit;

    constexpr auto table_format = "{:<8} {:<8} {:<20}\n";

    std::cout << std::format(table_format, "integer", "sum", "factorial");

    unsigned n{};
    unsigned sum{};
    unsigned long long factorial{1ULL};

    while (++n <= limit)
    {
        sum += n;
        factorial *= n;
        std::cout << std::format(table_format, n, sum, factorial);
    }
}