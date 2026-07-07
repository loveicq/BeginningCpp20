//Box.cppm
export module Box;

export class Box
{
public:
    Box() = default;
    Box(double length, double width, double height);

    double volume() const;

    double getLength() const;
    double getWidth() const;
    double getHeight() const;

    void setLength(double length);
    void setWidth(double width);
    void setHeight(double height);

private:
    double m_length{ 1.0 };
    double m_width{ 1.0 };
    double m_height{ 1.0 };
};