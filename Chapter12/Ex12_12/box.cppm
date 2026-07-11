//box.cppm
export module box;

export class Box
{
public:
    Box() :Box{ 1.0,1.0,1.0 } {}    // 委托默认构造函数
    Box(double length, double width, double height);

    double volume() const;  // 计算盒子体积的函数

    friend double surfaceArea(const Box& box);  // 用于表面积计算的友元函数

private:
    double m_length, m_width, m_height;
};