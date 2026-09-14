// Box.cppm
export module box;

import <compare>;   // For std::partial_ordering
import <ostream>;   // For std::ostream
import <algorithm>; // For std::max() and std::min()

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height)
        : m_length{std::max(length, width)},
          m_width{std::min(length, width)},
          m_height{height}
    {}

    double volume() const { return m_length * m_width * m_height; }

    double getLength() { return m_length; }
    double getWidth() { return m_width; }
    double getHeight() { return m_height; }

    std::partial_ordering operator<=>(const Box& aBox) const;
    std::partial_ordering operator<=>(double value) const;
    bool operator==(const Box& aBox) const = default;

    Box operator+(const Box& aBox) const;
    Box operator*(unsigned factor) const;
    Box operator/(unsigned divisor) const;

    Box& operator+=(const Box& aBox);
    Box& operator*=(unsigned factor);
    Box& operator/=(unsigned divisor);

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

export Box operator*(unsigned factor, const Box& aBox);
export std::ostream& operator<<(std::ostream& stream, const Box& aBox);