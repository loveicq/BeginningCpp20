// Carton.cppm
export module carton;

import box;
import <string>;
import <string_view>;
import <iostream>;

export class Carton : public Box
{
public:
    Carton() { std::cout << "Carton() called.\n"; }

    explicit Carton(std::string_view material) : m_material{material}
    {
        std::cout << "Carton(string_view) called.\n";
    }

    Carton(double side, std::string_view material) : Box{side}, m_material{material}
    {
        std::cout << "Carton(double,string_view) called.\n";
    }

    Carton(double length, double width, double height, std::string_view material)
        : Box{length, width, height}, m_material{material}
    {
        std::cout << "Carton(double,double,double,string_view) called.\n";
    }

    /*
    // Copy constructor (wrong)
    Carton(const Carton& carton) : m_material{carton.m_material} // 未显式指定Box对象构造函数，会调用默认Box()
    {
        std::cout << "Carton copy constructor" << std::endl;
    }
    */

    // Copy constructor (correct)
    Carton(const Carton& carton) : Box{carton}, m_material{carton.m_material}
    {
        std::cout << "Carton copy structor" << std::endl;
    }

    ~Carton() { std::cout << "Carton destructor.Material = " << m_material << std::endl; }

private:
    std::string m_material{"Cardboard"};
};