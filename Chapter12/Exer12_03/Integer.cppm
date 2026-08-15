// Integer.cppm
export module integer;

export class Integer
{
public:
    Integer() = default;
    Integer(int value);
    Integer(const Integer &obj);

    int getValue() const { return m_value; }

    Integer &add(const Integer &obj);
    Integer &subtract(const Integer &obj);
    Integer &multiply(const Integer &obj);

private:
    int m_value{0};
};