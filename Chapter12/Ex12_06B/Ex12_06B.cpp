//Ex12_06B.cpp
import <iostream>;
import Box;

int main()
{
    Box myBox{ 6.0, 6.0, 18.5 };
    std::cout << "Volume of the first Box object is " << myBox.volume() << std::endl;
}