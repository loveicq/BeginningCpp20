#include <iostream>

int main()
{
    unsigned count{};
    char ch{};

    std::cout << "Please enter a sequence of characters terminated by '#':" << std::endl;

    // We have to read at least one character so do-while is best
    do
    {
        std::cin >> ch;
        ++count;
    } while (ch != '#');

    // We do not count '#' as a character, so count must be adjusted
    --count;
    std::cout << "You entered " << count << " characters (not counting spaces and the terminal #)." << std::endl;
}