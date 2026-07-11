//Box.cppm
export module Box;
import <iostream>;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height);

    double volume() const;  //计算盒子体积的Const函数

    //非const重载（返回对尺寸变量的引用）
    double& length() { std::cout << "Non-const overload called.\n";return m_length; }
    double& width() { std::cout << "Non-const overload called.\n";return m_width; }
    double& height() { std::cout << "Non-const overload called.\n";return m_height; }

    // Const重载（返回对Const变量的引用）
    const double& length() const { std::cout << "Const overload called.\n";return m_length; }
    const double& width() const { std::cout << "Const overload called.\n";return m_width; }
    const double& height() const { std::cout << "Const overload called.\n";return m_height; }

    //尝试返回对const函数成员变量的非const引用
    // double& length() const { return m_length; }    //不允许编译！
    // double& width() const { return m_width; }
    // double& height() const { return m_height; }

private:
    double m_length{ 1.0 };
    double m_width{ 1.0 };
    double m_height{ 1.0 };
};