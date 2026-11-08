// ToughPack.cppm
export module boxes:tough_pack;

import <iostream>;
import :box;

export class ToughPack : public Box
{
public:
    using Box::Box;

private:
    double volume() const override
    {
        return 0.85 * m_length * m_width * m_height;
    }
};