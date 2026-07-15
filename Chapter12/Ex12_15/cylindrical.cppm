// cylindrical.cppm
export module cylindrical;

import <string_view>;
import <string>;

export class cylindricalBox
{
public:
    const static inline float{35.0f};
    const static inline float s_max_height{60.0f};
    const static inline std::string_view s_default_material{"paperboard"};
    cylindricalBox(float radius, float height,
                   std::string_view material = s_default_material);
    float volume() const;

private:
    const static inline float PI{3.141592f};

    float m_radius;
    float m_height;
    std::string m_material;
};