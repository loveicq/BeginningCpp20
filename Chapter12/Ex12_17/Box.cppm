// Box.cppm
export module box;          // 声明模块 box

import <iostream>;          // 导入标准库头文件作为模块
import <format>;

export class Box            // 导出 Box 类
{
public:
    Box() = default;        // 默认构造函数，使用成员初始值 1.0
    Box(double length, double width, double height)
        : m_length{ length }, m_width{ width }, m_height{ height }
    {
    }

    double volume() const   // 计算体积
    {
        return m_length * m_width * m_height;
    }

    int compare(const Box& box) const
    {
        if (volume() < box.volume())
            return -1;
        if (volume() == box.volume())
            return 0;
        return +1;
    }

    void listBox() const
    {
        // 使用 std::format 格式化输出（C++20 特性）
        std::cout << std::format("Box({:.1f},{:.1f},{:.1f})",
            m_length, m_width, m_height);
    }

private:
    double m_length{ 1.0 };   // 默认尺寸均为 1.0
    double m_width{ 1.0 };
    double m_height{ 1.0 };
};