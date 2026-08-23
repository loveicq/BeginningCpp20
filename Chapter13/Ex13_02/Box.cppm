// Box.cppm
export module box;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height} {}

    double volume() const { return m_length * m_width * m_height; }

    bool operator<(const Box& box) const { return volume() < box.volume(); }
    bool operator<(double value) const { return volume() < value; }

    double getLength() const { return m_length; }
    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

export bool operator<(double value, const Box& box) // 因成员函数只能有一个参数，所以此函数只能声明为非成员运算符重载函数
{
    return value < box.volume();
}