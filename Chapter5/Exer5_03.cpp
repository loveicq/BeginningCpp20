#include <iostream>
#include <cctype>

int main()
{
    unsigned total{};
    unsigned i{};
    const unsigned max_length{100};
    char text[max_length]{};

    std::cout << "Enter a line of text:" << std::endl;
    std::cin.getline(text, max_length);

    do
    {
        if (!std::isspace(text[i]))
        {
            ++total;
        }
        ++i;
    } while (text[i] != '\0' && text[i] != '#');

    std::cout << "You entered " << total << " non-blank characters. "
              << std::endl;
}