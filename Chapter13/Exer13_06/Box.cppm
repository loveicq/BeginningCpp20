// Box.cppm
export module box;

import <compare>;
import <format>;
import <ostream>;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{1.0} {}

    double volume() const { return m_length * m_width * m_height; }

    double getLength() const { return m_length; }
    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

    std::partial_ordering operator<=>(const Box& box) const
    {
        return volume() <=> box.volume();
    }
    std::partial_ordering operator<=>(double value) const
    {
        return volume() <=> value;
    }
    bool operator==(const Box& box) const = default;

    explicit operator bool() const { return volume() != 0; }

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

export std::ostream& operator<<(std::ostream& stream, const Box& box)
{
    stream << std::format("Box({:.1f},{:.1f},{:.1f})",
                          box.getLength(), box.getWidth(), box.getHeight());
    return stream;
}