// Carton.cppm
export module boxes:carton;

import :box;
import <string>;
import <string_view>;
import <algorithm>;

export class Carton : public Box
{
public:
    Carton(double length, double width, double height, std::string_view mat = "cardboard")
        : Box{length, width, height}, m_material{mat} {}

    double volume() const override
    {
        const double volume{(m_length - 0.5) * (m_width - 0.5) * (m_height - 0.5)};
        return std::max(volume, 0.0);
    }

private:
    std::string m_material;
};