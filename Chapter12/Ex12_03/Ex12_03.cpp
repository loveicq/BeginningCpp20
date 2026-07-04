// Ex12_03.cpp
import <iostream>;

class Box
{
  public:
    // Box() = default;
    Box(double length = 1.0, double width = 1.0, double height = 1.0);

    double volume();

  private:
    double m_length;
    double m_width;
    double m_height;
};

int main()
{
    Box firstBox{80.0, 50.0, 40.0};
    double firstBoxVolume{firstBox.volume()};

    std::cout << "Volume of Box object is " << firstBoxVolume << std::endl;

    Box secondBox; // 会调用默认构造函数创建对象secondBox
}

Box::Box(double length, double width, double height)
    : m_length{length}, m_width{width}, m_height{height}
{
    std::cout << "Box constructor called." << std::endl;
}

double Box::volume() { return m_length * m_width * m_height; }