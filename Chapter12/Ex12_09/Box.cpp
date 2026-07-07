//Box.cpp
module Box;
import <iostream>;

Box::Box(double length, double width, double height)
    : m_length{ length }, m_width{ width }, m_height{ height }
{
    std::cout << "Box constructor called." << std::endl;
}

double Box::volume() const
{
    return m_length * m_width * m_height;
}

double Box::getLength() const
{
    return m_length;
}

double Box::getWidth() const
{
    return m_width;
}

double Box::getHeight() const
{
    return m_height;
}

void Box::setLength(double length)
{
    if (length > 0)
        m_length = length;
}

void Box::setWidth(double width)
{
    if (width > 0)
        m_width = width;
}

void Box::setHeight(double height)
{
    if (height > 0)
        m_height = height;
}