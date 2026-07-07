// Box.cppm
export module Box;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height);

    double volume();

    double getLength() { return m_length; }
    double getWidth() { return m_width; }
    double getHeight() { return m_height; }

    Box& setLength(double length);
    Box& setWidth(double width);
    Box& setHeight(double height);

private:
    double m_length;
    double m_width;
    double m_height;
};