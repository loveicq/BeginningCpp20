#include <iostream>

int main()
{
    int num{};
    std::cout << "Input a integer: ";
    std::cin >> num;

    std::cout << "The number is "
              << (num <= 20 ? "not greater than 20." : (num > 20 && num <= 30 ? " greater than 20 and not greater than 30." : (num > 30 && num <= 100 ? " greater than 30 and not greater than 100." : "greater than 100.")))
              << std::endl;
}