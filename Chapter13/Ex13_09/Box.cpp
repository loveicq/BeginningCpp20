// Box.cpp
module box;

import <format>;
import <ostream>;

Box& Box::operator++()
{
    ++m_length;
    ++m_width;
    ++m_height;

    return *this;
}

const Box Box::operator++(int)
{
    auto copy(*this);
    ++(*this);

    return copy;
}

Box& Box::operator--()
{
    --m_length;
    --m_width;
    --m_height;

    return *this;
}

const Box Box::operator--(int)
{
    auto copy(*this);
    --(*this);

    return copy;
}

std::ostream& operator<<(std::ostream& stream, const Box& box)
{
    stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                          box.getLength(), box.getWidth(), box.getHeight());
    return stream;
}