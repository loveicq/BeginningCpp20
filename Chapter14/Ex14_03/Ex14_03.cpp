// Ex14_03.cpp
import <iostream>;
import carton;

int main()
{
    Carton carton(20.0, 30.0, 40.0, "Expanded polystyrene");
    std::cout << std::endl;

    Carton cartonCopy(carton);
    std::cout << std::endl;

    std::cout << "Volume of carton is " << carton.volume() << std::endl
              << "Volume of cartonCopy is " << cartonCopy.volume() << std::endl;
    // std::cout << "Hello world!" << std::endl;
}