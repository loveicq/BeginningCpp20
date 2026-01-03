#include <iostream>
#include <format>
#include <cctype>

int main()
{
    const size_t table_min{2};
    const size_t table_max{12};
    const size_t max_tries{3};
    size_t table{};
    char reply{};

    do
    {
        for (size_t count{1};; ++count)
        {
            std::cout << std::format("What size table would you like ({} to {})?", table_min, table_max);
            std::cin >> table;
            if (table >= table_min && table <= table_max)
            {
                break;
            }
            else if (count < max_tries)
            {
                std::cout << "Invalid input - try again.\n";
            }
            else
            {
                std::cout << "Invalid table size entered - yet again!\nSorry,only "
                          << max_tries << " allowed - program terminated." << std::endl;
                return 1;
            }
        }

        std::cout << std::format("{:>6}", '|');
        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i);
        }
        std::cout << std::endl;

        for (size_t i{}; i <= table + 1; ++i)
        {
            std::cout << "------";
        }
        std::cout << std::endl;

        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format("{:4} |", i);
            for (size_t j{1}; j <= table; ++j)
            {
                std::cout << std::format("{:4} |", i * j);
            }
            std::cout << std::endl;
        }

        std::cout << "Do you want another table (y or n)?";
        std::cin >> reply;
    } while (std::tolower(reply) == 'y');
}