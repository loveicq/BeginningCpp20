// Ex12_08A.cpp
import <iostream>;
import Box;

int main()
{
    Box myBox{ 3.0, 4.0, 5.0 };

    std::cout << "myBox dimensions are "
        << myBox.getLength()
        << " by " << myBox.getWidth()
        << " by " << myBox.getHeight()
        << std::endl;

    myBox.setLength(-20.0).setWidth(40.0).setHeight(10.0);

    std::cout << "myBox dimensions are now "
        << myBox.getLength()
        << " by " << myBox.getWidth()
        << " by " << myBox.getHeight()
        << std::endl;
}