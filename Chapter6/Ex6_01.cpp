#include <iostream>

int main()
{
    std::cout << sizeof(double) << " > " << sizeof(char16_t) << std::endl;
    std::cout << sizeof(double *) << " == " << sizeof(char16_t *) << std::endl;
}