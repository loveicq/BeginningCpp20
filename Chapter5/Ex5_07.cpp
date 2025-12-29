#include <iostream>
#include <format>
#include <cctype>

int main()
{
    size_t table{};
    const size_t table_min{2};
    const size_t table_max{12};
    char reply{};

    do
    {
        std::cout << std::format("What size table would you like ({} to {})? ", table_min, table_max);
        std::cin >> table;
        std::cout << std::endl;

        if (table < table_min || table > table_max)
        {
            std::cout << "Invalid table size entered.Program terminated." << std::endl;
            return 1;
        }

        std::cout << std::format("{:>6}", '|');

        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i);
        }
        std::cout << std::endl;

        for (size_t i{}; i <= table; ++i)
        {
            std::cout << "------";
        }
        std::cout << "-----";
        std::cout << std::endl;
        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i);

            for (size_t j{1}; j <= table; ++j)
            {
                std::cout << std::format(" {:3} |", i * j);
            }
            std::cout << std::endl;
        }

        std::cout << "\nDo you want another table(y or n)? ";
        std::cin >> reply;
    } while (std::tolower(reply) == 'y');
}