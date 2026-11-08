// Box.cppm
export module boxes:box;

import <iostream>;

export class Box
{
public:
    Box() : Box{1.0, 1.0, 1.0} {}
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height} {}

    void showVolume() const
    {
        std::cout << "Box usable volume is " << volume() << std::endl;
    }

    virtual double volume() const
    {
        return m_length * m_height * m_width;
    }

protected:
    double m_length, m_width, m_height;
};