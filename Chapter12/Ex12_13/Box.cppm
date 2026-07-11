//Box.cppm
export module box;

export class Box
{
public:
    Box();  //此处不能写成Box()=default;，因为函数定义时有std::...等自定义内容
    Box(double length, double width, double height);
    Box(double side);
    Box(const Box& box);

    double volume() const { return m_length * m_width * m_height; }

private:
    double m_length{ 1.0 };
    double m_width{ 1.0 };
    double m_height{ 1.0 };
};