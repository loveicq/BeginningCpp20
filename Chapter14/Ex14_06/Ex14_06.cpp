// Ex14_06.cpp

import carton;
import <iostream>;

int main()
{
    Carton carton;
    Carton candyCarton{50.0, 30.0, 20.0, "SBB"};

    std::cout << "Volume of carton is " << carton.volume() << std::endl
              << "Volume of candyCarton is " << candyCarton.volume() << std::endl;
}