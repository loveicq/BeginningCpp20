//Box.cpp
module Box;
import <iostream>;

//构造函数定义
Box::Box(double length, double width, double height)
: m_length{length}, m_width{width}, m_height{height}
{
    std::cout << "Box constructor called." << std::endl;
}

// Const成员函数定义
double Box::volume() const
{
    return m_length * m_width * m_height;
}

//修改const成员函数的可变成员变量
void Box::printVolume() const
{
    std::cout << "The volume of this box is " << volume() << std::endl;
    std::cout << "printVolume has been called " << ++m_count << " time(s)" << std::endl;
}