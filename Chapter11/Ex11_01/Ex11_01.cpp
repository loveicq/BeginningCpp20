// Ex11_01.cpp - Consuming your own module
import<iostream>;
import<format>;
import math;

int main()
{
    std::cout << "Lambda squared: " << square(lambda) << std::endl;

    int number;
    std::cout << "\nPlease enter an odd number: ";
    std::cin >> number;
    std::cout << std::endl;

    switch (getOddity(number))
    {
        using enum Oddity;
    case Odd:
        std::cout
            << "Well done! And remember: you have to be odd to be number one!";
        break;
    case Even:
        std::cout << std::format("Odd, {} seems to be even?", number);
        break;
    }
    std::cout << std::endl;

    std::cin.ignore();
    std::cin.get();
}