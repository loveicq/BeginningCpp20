// cylindrical.cpp
module cylindrical;

import <iostream>;

cylindricalBox::cylindricalBox(float radius, float height, std::string_view material)
    : m_radius{radius}, m_height{height}, m_material{material}
{
    std::cout << "Box constructed consisting of " << material;
    if (material == s_default_material)
    {
        std::cout << " (the default material!)";
    }
    std::cout << std::endl;
}

float cylindricalBox::volume() const
{
    return PI * m_radius * m_radius * m_height;
}
