// Ex12_15.cpp
import <iostream>;
import cylindrical;

int main()
{
    cylindricalBox bigBox{1.23f, cylindricalBox::s_max_height,
                          cylindricalBox::s_default_material};
    std::cout << "The volume of bigBox is " << bigBox.volume() << std::endl;
}