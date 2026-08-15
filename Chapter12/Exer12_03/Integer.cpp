// Integer.cpp
module integer;

Integer::Integer(int value)
    : m_value{value} {}

Integer::Integer(const Integer &obj)
    : m_value{obj.m_value} {}

Integer &Integer::add(const Integer &obj)
{
    m_value += obj.m_value;
    return *this;
}

Integer &Integer::multiply(const Integer &obj)
{
    m_value *= obj.m_value;
    return *this;
}

Integer &Integer::subtract(const Integer &obj)
{
    m_value -= obj.m_value;
    return *this;
}