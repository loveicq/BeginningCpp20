// Box.cppm
export module box;
import <iostream>;

export class Box
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

Box::Box(double length, double width, double height)
    : m_length{length}, m_width{width}, m_height{height}
{
    std::cout << "Box constructor called." << std::endl;
}

double Box::volume()
{
    return m_length * m_width * m_height;
}