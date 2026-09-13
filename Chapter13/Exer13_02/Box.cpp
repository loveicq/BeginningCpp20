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
    return Box{std::max(m_length, aBox.m_length),
               std::max(m_width, aBox.m_width),
               m_height + aBox.m_height};
}

Box Box::operator*(unsigned n) const
{
    return Box{m_length, m_width, m_height * n};
}

std::ostream& operator<<(std::ostream& stream, const Box& aBox)
{
    stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                          aBox.getLength(), aBox.getWidth(), aBox.getHeight());
    return stream;
}

Box operator*(unsigned n, const Box& aBox)
{
    return Box{aBox.getLength(), aBox.getWidth(), n * aBox.getHeight()};
}