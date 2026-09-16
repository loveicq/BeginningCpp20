// Rational.cppm
export module rational;
import <iostream>;

export class Rational
{
public:
    Rational(int numerator = 0, int denominator = 1)
        : m_numerator{numerator}, m_denominator{denominator} {}

    int getNumerator() const { return m_numerator; }
    int getDenominator() const { return m_denominator; }

    void setNumerator(int numerator) { m_numerator = numerator; }
    void setDenominator(int denominator) { m_denominator = denominator; }

    explicit operator double() const { return static_cast<double>(m_numerator) / m_denominator; }
    explicit operator float() const { return static_cast<float>(m_numerator) / m_denominator; }

    auto operator<=>(const Rational& other)
    {
        return m_numerator * other.m_denominator <=> other.m_numerator * m_denominator;
        // *this=a/b, other=c/d   通分：a*d/b*d vs c*b/d*b, 分母相同，比分子即可：a*d<=>c*b
    }

    auto operator<=>(double value)
    {
        return static_cast<double>(*this) <=> value;
    }

    bool operator==(const Rational& other)
    {
        return m_numerator * other.m_denominator == other.m_numerator * m_denominator;
        // 数学原理如同上面auto operator<=>(const Rational& other)
    }

    bool operator==(double value)
    {
        return static_cast<double>(*this) == value;
    }

    Rational operator-() const { return Rational{-m_numerator, m_denominator}; }

    explicit operator bool() const { return m_numerator != 0; }

    Rational& operator+=(const Rational& other)
    {
        m_numerator   = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
        m_denominator = m_denominator * other.m_denominator;
        return *this;
    }

private:
    int m_numerator, m_denominator;
}