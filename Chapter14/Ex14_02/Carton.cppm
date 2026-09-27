// Carton.cppm
export module carton;

import <string>;
import <string_view>;
import <iostream>;
import box;

export class Carton : public Box
{
public:
    Carton() { std::cout << "Carton() called.\n"; }

    explicit Carton(std::string_view material) : m_material{material}
    {
        std::cout << "Carton(string_view) called.\n";
    }

    Carton(double side,std::string_view material):Box(side),m_material{material}
    {
        std::cout << "Carton(double,string_view) called.\n";
    }

    Carton(double length,double width,double height,std::string_view material)
    :Box(length,width,height),m_material{material}
    {
        std::cout << "Carton(double,double,double,string_view) called.\n";
    }

private:
    std::string m_material{"Cardboard"};
};