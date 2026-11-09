// Carton.cppm
export module boxes:carton;

import :box;
import <string>;
import <string_view>;
import <iostream>;

export class Carton : public Box
{
public:
    Carton(double length, double width, double height, std::string_view mat = "cardboard")
        : Box{length, width, height}, m_material{mat} {}

    double volume(int i=50) const override
    {
        std::cout << "(Carton argument i = " << i << ") ";
        const double inner_volume{(m_length - 0.5) * (m_width - 0.5) * (m_height - 0.5)};
        return inner_volume > 0.0 ? inner_volume : 0.0;
    }

private:
    std::string m_material;
};