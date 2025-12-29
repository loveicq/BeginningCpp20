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

        // 打印列表头
        std::cout << std::format("{:>6}", '|'); // 打印表头第一个竖线
        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i); // 打印表头后面的数字和竖线
        }
        std::cout << std::endl;

        // 打印表头下面的分隔线
        for (size_t i{}; i <= table + 1; ++i)
        {
            std::cout << "------";
        }
        std::cout << std::endl;

        // 外循环打印行内容
        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i); // 打印行表头

            // 内循环打印列内容
            for (size_t j{1}; j <= table; ++j)
            {
                std::cout << std::format(" {:3} |", i * j);
            }
            std::cout << std::endl; // 打印完最后一列换到下一行
        }

        std::cout << "\nDo you want another table(y or n)? ";
        std::cin >> reply;
    } while (std::tolower(reply) == 'y');
}