// Carton.cppm
export module carton;

import box;
import <string_view>;
import <string>;
import <iostream>;

export class Carton : private Box // 私有继承，则继承的所有成员都是私有
{
public:
    explicit Carton(std::string_view mat = "Cardboard") : m_material{mat}
    {
        std::cout << "Carton() called." << std::endl;
    }
    using Box::volume; // 声明Box::volume()为公有

private:
    std::string m_material;
};
