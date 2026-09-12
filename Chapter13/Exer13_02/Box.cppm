// Box.cppm
export module box;

import <ostream>;
import <format>;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height} {}

    friend Box operator*(unsigned n, const Box& box);
    friend std::ostream& operator<<(std::ostream& stream, const Box& aBox);

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

export Box operator*(unsigned n, const Box& box)
{
    return Box{box.m_length, box.m_width, n * box.m_height};
}

export std::ostream& operator<<(std::ostream& stream, const Box& aBox)
{
    stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                          aBox.m_length, aBox.m_width, aBox.m_height);
    return stream;
}