//Ex12_09.cpp
import <iostream>;
import Box;

int main()
{
    const Box myBox{ 3.0, 4.0, 5.0 };

    std::cout << "myBox dimensions are " << myBox.getLength()
        << " by " << myBox.getWidth()
        << " by " << myBox.getHeight()
        << std::endl;

    //由于myBox对象是const对象，而下面三个函数声明时都没有const，所以都无法调用，编译不能通过
    // myBox.setLength(-20.0);
    // myBox.setWidth(40.0);
    // myBox.setHeight(10.0);

    std::cout << "myBox dimensions are " << myBox.getLength()
        << " by " << myBox.getWidth()
        << " by " << myBox.getHeight()
        << std::endl;

    std::cout << "myBox's volume is " << myBox.volume() << std::endl;
}