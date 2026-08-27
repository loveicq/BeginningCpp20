// Box.cppm
export module box;

import <compare>;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height} {}

    double volume() const { return m_length * m_width * m_height; }

    double getLength() const { return m_length; }
    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

    std::partial_ordering operator<=>(const Box& box) const { return volume() <=> box.volume(); } // 自定义<=>,比较体积大小，而非比较成员变量大小
    bool operator==(const Box& box) const = default;                                              // 默认==，逐个成员变量比较大小，而非比较体积大小
    // 对象与对象的比较，通过上面的<=>和==重载，即包含了<、<=、>、>=、==、!=这6个运算符了
    // 仅重载<=>是不包括==和!=这2个运算符的

    std::partial_ordering operator<=>(const double value) const { return volume() <=> value; } // 自定义<=>，比较体积，而非成员变量
    // 对象与数值的比较，需要单独重载<=>

    // 如果本例不比较体积大小(自定义)，仅比较成员变量大小(默认)，则只需要一行默认的<=>重载就足够了：
    // std::partial_ordering operator<=>(const Box& box) const = default;   //包括==、!=、<、<=、>、>=6个运算符

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};