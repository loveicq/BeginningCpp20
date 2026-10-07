// Ex14_07A.cpp
import <iostream>;
import cereal;

int main()
{
    CerealPack cornflakes{8.0, 3.0, 10.0, "Cornflakes"};

    std::cout << "cornflakes volume is " << static_cast<Carton&>(cornflakes).volume() << std::endl
              << "cornflakes weight is " << static_cast<FoodContainer&>(cornflakes).getWeight() << std::endl;
}