// Box.cppm
export module boxes:box;

import <iostream>;

export class Box
{
public:
    Box() : Box{1.0, 1.0, 1.0} {}
    Box(double l, double w, double h) : m_length{l}, m_width{w}, m_height{h} {}

    ~Box()
    {
        std::cout << "Box destructor called" << std::endl;
    }

    void showVolume() const
    {
        std::cout << "Box usable volume is " << volume() << std::endl;
    }

    virtual double volume() const
    {
        return m_length * m_width * m_height;
    }

protected:
    double m_length, m_width, m_height;
};