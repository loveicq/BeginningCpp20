// Ex12_01A
import <iostream>;

class Box
{
  public:
    // Box(){}    //显式定义的默认构造函数
    Box() = default; // 默认构造函数

    // 构造函数
    Box(double length, double width, double height)
    {
        std::cout << "Box constructor called." << std::endl;
        m_length = length;
        m_width = width;
        m_height = height;
    }

    double volume() { return m_length * m_width * m_height; }

  private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

int main()
{
    Box firstBox{80.0, 50.0, 40.0};
    double firstBoxVolume{firstBox.volume()};
    std::cout << "Volume of Box object is " << firstBoxVolume << std::endl;

    Box secondBox; // 不再导致编译器错误消息
}