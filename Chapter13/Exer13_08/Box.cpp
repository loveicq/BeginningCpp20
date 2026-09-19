// Box.cpp
module box;

import <format>;

std::partial_ordering Box::operator<=>(const Box& box) const
{
    return volume() <=> box.volume();
}

std::partial_ordering Box::operator<=>(double value) const
{
    return volume() <=> value;
}

Box& Box::operator+=(const Box& box)
{
    m_length = std::max(m_length, box.m_length);
    m_width  = std::max(m_width, box.m_width);
    m_height += box.m_height;
    return *this;
}

Box Box::operator+(const Box& box) const
{
    Box copy{*this};
    copy += box;
    return copy;
}

std::ostream& operator<<(std::ostream& stream, const Box& box)
{
    stream << std::format("Box({:.1f},{:.1f},{:.1f})", box.getLength(), box.getWidth(), box.getHeight());
    return stream;
}