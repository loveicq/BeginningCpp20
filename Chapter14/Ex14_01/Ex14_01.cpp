// Ex14_01.cpp
import <iostream>;
import box;
import carton;

int main()
{
    Box box{40.0, 30.0, 20.0};
    Carton carton;
    Carton chocolateCarton{"Solid bleached board"}; // Good old SBB

    std::cout << "box occupies " << sizeof box << " bytes" << std::endl;
    std::cout << "carton occupies " << sizeof carton << " bytes" << std::endl;
    std::cout << "candyCarton occupies " << sizeof chocolateCarton << " bytes" << std::endl;

    std::cout << "box's volume is " << box.volume() << std::endl;
    std::cout << "carton's volume is " << carton.volume() << std::endl;
    std::cout << "chocolateCarton's volume is " << chocolateCarton.volume() << std::endl;

    std::cout << "chocolateCarton's length is " << chocolateCarton.getLength() << std::endl;

    // Uncomment any of the following for an error...
    // box.m_length = 10.0;
    // chocolateCarton.m_length = 10.0;
}