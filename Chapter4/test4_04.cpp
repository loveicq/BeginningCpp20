#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int ticket_number{};
    std::cin >> ticket_number;

    switch (ticket_number)
    {
    case 147:
        std::cout << "You win first prize!" << std::endl;
        break;
    case 387:
    case 123:
        std::cout << "You win second prize!" << std::endl;
        break;
    case 929:
        std::cout << "You win a special bonus prize!" << std::endl;
        [[fallthrough]]; // 此语句告诉编译器和阅读代码的人,我故意使用了贯穿行为.
    case 29:
    case 78:
        std::cout << "You win third prize!" << std::endl;
        break;
    default:
        std::cout << "Sorry, you lose!" << std::endl;
        break;
    }
}