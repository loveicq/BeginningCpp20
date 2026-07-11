//box.cpp
module box;

import <iostream>;

// 构造函数定义
Box::Box(double length, double width, double height)
    : m_length{ length }, m_width{ width }, m_height{ height }
{
    std::cout << "Box constructor called." << std::endl;
}

// 常量成员函数定义
double Box::volume() const
{
    return m_length * m_width * m_height;
}

double surfaceArea(const Box& box)
{
    return 2.0 * (box.m_length * box.m_width + box.m_length * box.m_height
        + box.m_width * box.m_height);
}