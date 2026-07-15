// Box.cpp
module Box;
import <iostream>;

Box::Box(double length, double width, double height)
    : m_length{length}, m_width{width}, m_height{height}
{
    ++s_object_count;
    std::cout << "Box constructor 1 called." << std::endl;
}

Box::Box(double side) : Box{side, side, side}
{
    // 不要在转发构造函数中增加 s_object_count：
    // 在被转发的构造函数中已经增加过了！
    std::cout << "Box constructor 2 called." << std::endl;
}

Box::Box()
{
    ++s_object_count;
    std::cout << "Default Box constructor called." << std::endl;
}

Box::Box(const Box &box)
    : m_length{box.m_length}, m_width{box.m_width}, m_height{box.m_height}
{
    ++s_object_count;
    std::cout << "Box copy constructor called." << std::endl;
}

Box::~Box()
{
    std::cout << "Box destructor called." << std::endl;
    --s_object_count;
}