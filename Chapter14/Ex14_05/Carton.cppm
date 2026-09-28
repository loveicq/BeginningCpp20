// Carton.cppm
export module carton;

import box;
import <string>;
import <string_view>;
import <iostream>;

export class Carton : public Box
{
    using Box::Box;

public:
    Carton() = default;

    Carton(double length, double width, double height, std::string_view mat)
        : Box{length, width, height}, m_material{mat} { //此处指定基类构造函数
        std::cout << "Carton(double,double,double,string_view) called.\n";
    }

private:
    std::string m_material{"Cardboard"};
};