// Carton.cppm
export module carton;

import box;
import <iostream>;

export class Carton : public Box
{
public:
    Carton()
    {
        std::cout << "Carton() called.\n";
    }

    explicit Carton(std::string_view material) : m_material{material}
    {
        std::cout << "Carton(string_view) called.\n";
    }

    Carton(double length, double width, double height, std::string_view material)
        : Box{length, width, height}, m_material{material} // 指定基类构造函数
    {
        std::cout << "Carton(double,double,double,string_view) called.\n";
    }

    Carton(double length, double width, double height, std::string_view material, double density, double thickness)
        : Carton{length, width, height, material}
    {
        m_thickness = thickness;
        m_density   = density;
        std::cout << "Carton(double,double,double,string_view,double,double) called.\n";
    }

    Carton(const Carton& carton) : Box{carton}, m_material{carton.m_material}, m_thickness{carton.m_thickness}, m_density{carton.m_density}
    {
        std::cout << "Carton copy constructor" << std::endl;
    }

    ~Carton()
    {
        std::cout << "Carton destructor.Material = " << m_material << std::endl;
    }

    double getWeight() const
    {
        return 2.0 * (m_length * m_width + m_width * m_height + m_height * m_length) * m_thickness * m_density;
    }

private:
    std::string m_material{"Cardboard"}; // 材料
    double m_thickness{0.125};           // 厚度
    double m_density{0.2};               // 密度
};