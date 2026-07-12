//Box.cppm
export module box;
import <iostream>;

export class Box
{
public:
    Box();  //默认构造函数
    Box(double side);   //立方体构造函数
    Box(const Box& box);    //副本构造函数
    Box(double length, double width, double height);

    double volume() const { return m_length * m_width * m_height; }

    size_t getObjectCount() const { return s_object_count; }
private:
    double m_length{ 1.0 };
    double m_width{ 1.0 };
    double m_height{ 1.0 };
    static inline size_t s_object_count{};  //创建过的对象总数
};