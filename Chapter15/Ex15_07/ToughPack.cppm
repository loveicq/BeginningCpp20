// ToughPack.cppm
export module boxes:tough_pack;

import :box;
import <iostream>;

export class ToughPack : public Box
{
public:
    using Box::Box;

    ~ToughPack()
    {
        std::cout << "ToughPack destructor called" << std::endl;
    }

    double volume() const override
    {
        return 0.85 * m_length * m_width * m_height;
    }
};