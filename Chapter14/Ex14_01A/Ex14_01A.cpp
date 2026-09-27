// Ex14_01A.cpp
import <iostream>;
import box;
import carton;

int main()
{
    Box box{40.0, 30.0, 20.0};
    Carton carton;
    Carton chocolateCarton{"Solid bleached board"};

    std::cout << "box occupies " << sizeof box << " bytes" << std::endl;
    std::cout << "carton occupies " << sizeof carton << " bytes" << std::endl;
    std::cout << "candyCarton occupies " << sizeof chocolateCarton << " bytes" << std::endl;

    std::cout << "box volume is " << box.volume() << std::endl;
    std::cout << "carton volume is " << carton.volume() << std::endl;
    std::cout << "chocolateCarton volume is " << chocolateCarton.volume() << std::endl;

    // std::cout << "chocolateCarton length is " << chocolateCarton.getLenth() << std::endl; // "getLenth": 不是 "Carton" 的成员

    // box.m_length             = 10.0; // “Box::m_length”: 无法访问 private 成员(在“Box”类中声明)
    // chocolateCarton.m_length = 10.0; // “Box::m_length”: 无法访问 private 成员(在“Box”类中声明)
}