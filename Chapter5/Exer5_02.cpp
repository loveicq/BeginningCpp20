#include <iostream>
#include <cctype>
#include <format>

int main()
{
    unsigned count{};
    long long total{};

    while (true)
    {
        int n{};
        std::cout << "Enter an integer: ";
        std::cin >> n;
        total += n;
        ++count;

        char yesNo{};
        std::cout << "Do you want to enter another(y/n)? ";
        std::cin >> yesNo;
        if (std::tolower(yesNo) == 'n')
        {
            break;
        }
    }

    std::cout << std::format("Total:{},Average:{:.2f}.", total, static_cast<double>(total) / count)
              << std::endl;
}