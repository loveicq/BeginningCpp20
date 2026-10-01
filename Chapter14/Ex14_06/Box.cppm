// Box.cppm
export module box;

import <iostream>;
import <format>;
import <ostream>;

export class Box
{
public:
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height}
    {
        std::cout << "Box(double,double,double) called.\n";
    }

    explicit Box(double side) : Box{side, side, side}
    {
        std::cout << "Box(double) called.\n";
    }

    Box(const Box& box) : m_length{box.m_length}, m_width{box.m_width}, m_height{box.m_height}
    {
        std::cout << "Box copy constructor" << std::endl;
    }

    Box() { std::cout << "Box() called.\n"; }

    ~Box() { std::cout << "Box destructor" << std::endl; }

    double volume() const { return m_length * m_width * m_height; }
    double getLength() const { return m_length; }
    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

protected:
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