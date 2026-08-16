// Integer.cpp
/*****************************************************************\
要实现 printCount()，首先需要一个静态成员变量来存储对象计数。每个构造
函数都应该递增该计数，并且需要添加一个析构函数来递减它。
\*****************************************************************/
module integer;
import <iostream>;

Integer::Integer(int value) : m_value{value}
{
    ++s_count;
    std::cout << "Object created." << std::endl;
}

Integer::Integer(const Integer& obj) : m_value{obj.m_value}
{
    ++s_count;
    std::cout << "Object created by copy constructor." << std::endl;
}

Integer::~Integer()
{
    --s_count;
    std::cout << "Object deleted." << std::endl;
}

void Integer::show() const
{
    std::cout << "Value is " << m_value << std::endl;
}

int Integer::compare(const Integer& obj) const
{
    if (m_value < obj.m_value)
        return -1;
    else if (m_value == obj.m_value)
        return 0;
    return 1;
}

void Integer::printCount()
{
    std::cout << "There are now " << s_count << " Integer object(s)." << std::endl;
}