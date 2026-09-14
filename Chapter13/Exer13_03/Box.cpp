// Box.cpp
module box;

import <format>;

std::partial_ordering Box::operator<=>(const Box& aBox) const
{
    return volume() <=> aBox.volume();
}

std::partial_ordering Box::operator<=>(double value) const
{
    return volume() <=> value;
}

Box Box::operator+(const Box& aBox) const
{
    Box copy{*this};
    copy += aBox;
    return copy;
}

Box Box::operator*(unsigned factor) const
{
    Box copy{*this};
    copy *= factor;
    return copy;
}

Box Box::operator/(unsigned divisor) const
{
    Box copy{*this};
    copy /= divisor;
    return copy;
}

Box& Box::operator+=(const Box& aBox)
{
    m_length = std::max(m_length, aBox.m_length);
    m_width  = std::max(m_width, aBox.m_width);
    m_height += aBox.m_height;
    return *this;
}

Box& Box::operator*=(unsigned factor)
{
    m_length *= factor;
    m_width *= factor;
    m_height *= factor;
    return *this;
}

Box& Box::operator/=(unsigned divisor)
{
    m_length /= divisor;
    m_width /= divisor;
    m_height /= divisor;
    return *this;
}

Box operator*(unsigned factor, const Box& aBox)
{
    return aBox * factor;
}

std::ostream& operator<<(std::ostream& stream, const Box& aBox)
{
    stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                          aBox.getLength(), aBox.getWidth(), aBox.getHeight());
    return stream;
}
