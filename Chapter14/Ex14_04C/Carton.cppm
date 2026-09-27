// Carton.cppm
export module carton;

import box;
import <string>;
import <string_view>;
import <iostream>;

export class Carton : public Box
{
private:
    std::string m_material{"Cardboard"};

public:
    Carton() = default; // “Carton::Carton(void) noexcept(false)”: 由于 基类 调用已删除或不可访问的函数“Box::Box(void)”，因此已隐式删除函数

    Carton(double side, std::string_view material) : Box{side}, m_material{material}
    {
        std::cout << "Carton(double,string_view) called.\n";
    }

    Carton(double length, double width, double height, std::string_view material)
        : Box{length, width, height}, m_material{material}
    {
        std::cout << "Carton(double,double,double,string_view) called.\n";
    }
};