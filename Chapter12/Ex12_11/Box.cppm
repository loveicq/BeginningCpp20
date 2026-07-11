//Box.cppm
export module Box;

export class Box
{
public:
    //构造函数
    Box() = default;
    Box(double length, double width, double height);

    double volume() const;  //计算盒子体积的函数
    void printVolume() const;   ////输出盒子的体积（const!）

    //提供访问成员变量值的函数（都是const!）
    double getLength() const { return m_length; }
    double getWidth()   const { return m_width; }
    double getHeight() const { return m_height; }

    //设置成员变量值的函数（不是const!）
    void setLength(double length) { if (length > 0) m_length = length; }
    void setWidth(double width) { if (width > 0)    m_width = width; }
    void setHeight(double height) { if (height > 0)  m_height = height; }

private:
    double m_length{ 1.0 };
    double m_width{ 1.0 };
    double m_height{ 1.0 };
    mutable unsigned m_count{}; //计算调用printVolume（）的次数
};