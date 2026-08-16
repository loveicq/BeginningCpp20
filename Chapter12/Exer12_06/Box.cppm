// Box.cppm
export module box;

import <iostream>;
import <format>;

export class Box
{
public:
    Box() = default; // 声明了任何其他构造函数，编译器就不再自动生成默认构造函数，所以须显式声明它
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height} {};

    double volume() const
    {
        return m_length * m_width * m_height;
    }

    int compare(const Box& box) const
    {
        if (volume() < box.volume())
            return -1;
        else if (volume() == box.volume())
            return 0;
        return 1;
    }

    void listBox() const
    {
        std::cout << std::format("Box({:.1f},{:.1f},{:.1f})\n", m_length, m_width, m_height);
    }

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};