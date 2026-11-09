// Box.cppm
export module boxes:box;

import <iostream>;

export class Box
{
public:
    Box() : Box{1.0, 1.0, 1.0} {};
    Box(double length, double width, double height)
        : m_length{length}, m_width{width}, m_height{height} {}

    void showVolume() const
    {
        std::cout << "Box usable volume is " << volume() << std::endl;
    }

    virtual double volume(int i = 5) const
    {
        std::cout << "(Box argument i = " << i << ") ";
        return m_length * m_width * m_height;
    }

protected:
    double m_length, m_width, m_height;
};