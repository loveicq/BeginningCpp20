#include <iostream>
#include <cctype>

int main()
{
    char reply{};
    int count{};
    double temperature{};
    double total{};

    do
    {
        std::cout << "Enter a temperature reading: ";
        std::cin >> temperature;

        total += temperature;
        ++count;

        std::cout << "Do you want to enter another?(y/n): ";
        std::cin >> reply;

    } while (std::tolower(reply) == 'y');

    std::cout << "The average temperature is " << total / count << std::endl;
}