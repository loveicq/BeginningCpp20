// Box.cppm
export module box;

import <compare>;
import <ostream>;
import <format>;

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

    auto operator<=>(const Box& box) const { return volume() <=> box.volume(); }
    auto operator<=>(double value) const { return volume() <=> value; }

    bool operator==(const Box& box) const = default;

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

export std::ostream& operator<<(std::ostream& stream, const Box& box)
{
    stream << std::format("Box({:.1f},{:.1f},{:.1f})", box.getLength(), box.getWidth(), box.getHeight());
    /*
    ① std::format(...) → 先把格式串构造成一个 std::string
    ② stream << std::string → 调用标准库已有的成员 operator<<，把字符串写入流
    ③ 整个表达式返回 stream 的引用（供 return 使用）
    */
    return stream;
}