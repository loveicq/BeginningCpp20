//Ex12_12.cpp
// Using a friend function of a class

import <iostream>;
import <memory>;
import box;

int main()
{
    Box box1{ 2.2,1.1,0.5 };
    Box box2;
    auto box3{ std::make_unique<Box>(15.0,20.0,8.0) };

    std::cout << "Volume of box1 = " << box1.volume() << std::endl;
    std::cout << "Surface area of box1 = " << surfaceArea(box1) << std::endl;

    std::cout << "Volume of box2 = " << box2.volume() << std::endl;
    std::cout << "Surface area of box2 = " << surfaceArea(box2) << std::endl;

    std::cout << "Volume of box3 = " << box3->volume() << std::endl;
    std::cout << "Surface area of box3 = " << surfaceArea(*box3) << std::endl;
}