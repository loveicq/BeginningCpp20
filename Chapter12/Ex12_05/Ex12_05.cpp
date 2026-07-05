// Ex12_05.cpp
import <iostream>;

class Box
{
public:
    Box() = default;
    Box(double length, double width, double height);
    Box(double side);

    double volume();

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};

int main()
{
    Box box1{2.0, 3.0, 4.0};
    Box box2{5.0};
    std::cout << "box1 volume = " << box1.volume() << std::endl;
    std::cout << "box2 volume = " << box2.volume() << std::endl;
}

Box::Box(double length, double width, double height)
    : m_length{length}, m_width{width}, m_height{height}
{
    std::cout << "Box constructor 1 called." << std::endl;
}

Box::Box(double side) : Box{side, side, side}
{
    std::cout << "Box constructor 2 called." << std::endl;
}

double Box::volume()
{
    return m_length * m_width * m_height;
}