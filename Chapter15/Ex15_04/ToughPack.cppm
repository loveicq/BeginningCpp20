// ToughPack.cppm
export module boxes:tough_pack;

import :box;
import <iostream>;

export class ToughPack : public Box
{
public:
    using Box::Box;

    double volume(int i = 500) const override
    {
        std::cout << "(ToughPack argument i = " << i << ") ";
        return 0.85 * m_length * m_width * m_height;
    }
};