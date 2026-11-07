// ToughPack.cppm
export module boxes:tough_pack;
import :box;

export class ToughPack : public Box
{
public:
    using Box::Box;
    double volume() const { return 0.85 * m_length * m_width * m_height; }
};