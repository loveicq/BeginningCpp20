// Ex14_07B.cpp
import <iostream>;
import cereal;

int main()
{
    CerealPack cornflakes{8.0, 3.0, 10.0, "Cornflakes"};

    std::cout << "cornflakes volume is " << cornflakes.volume() << std::endl
              << "cornflakes weight is " << cornflakes.getWeight() << std::endl;
}