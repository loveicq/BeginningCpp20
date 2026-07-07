// Box.cppm
export module Box;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height);

    double volume();

    double getLength();
    double getWidth();
    double getHeight();

    Box &setLength(double length);
    Box &setWidth(double width);
    Box &setHeight(double height);

private:
    double m_length;
    double m_width;
    double m_height;
};