// Ex12_02.cpp
import <iostream>;

class Box
{
  public:
    Box() = default;
    Box(double length, double width, double height);

    double volume();

  private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

int main()
{
    Box firstBox{80.0, 50.0, 40.0}; // 初始化列表赋值给构造函数
    double firstBoxVolume{firstBox.volume()};

    std::cout << "Volume of Box object is " << firstBoxVolume << std::endl;

    Box secondBox;
}

Box::Box(double length, double width, double height)
{
    std::cout << "Box constructor called." << std::endl;

    m_length = length;
    m_width = width;
    m_height = height;
}

double Box::volume() { return m_length * m_width * m_height; }