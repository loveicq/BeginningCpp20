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

    void setLength(double length)
    {
        if (length > 0)
            m_length = length;
    }
    void setWidth(double width)
    {
        if (width > 0)
            m_width = width;
    }
    void setHeight(double height)
    {
        if (height > 0)
            m_height = height;
    }

private:
    double m_length{1.0};
    double m_width{1.0};
    double m_height{1.0};
};