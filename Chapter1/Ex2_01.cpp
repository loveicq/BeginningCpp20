#include <iostream>
int main()
{
    int apple_count{15};
    int orange_count{5};
    int fruit_total{apple_count + orange_count};

    std::cout << "The value of apple_count is " << apple_count << std::endl;
    std::cout << "The value of orange_count is " << orange_count << std::endl;
    std::cout << "The value of fruit_count is " << fruit_total << std::endl;
    std::cin.get();
    return 0;
}