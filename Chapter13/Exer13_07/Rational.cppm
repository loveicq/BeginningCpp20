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

    // a/b  =>  小数 = a / b
    explicit operator double() const { return static_cast<double>(m_numerator) / m_denominator; }
    explicit operator float() const { return static_cast<float>(m_numerator) / m_denominator; }

    // a/b <=> c/d  通分后分母相同，比较分子大小：a*d <=> c*b
    auto operator<=>(const Rational& other) const
    {
        return m_numerator * other.m_denominator <=> other.m_numerator * m_denominator;
    }

    auto operator<=>(double value) const
    {
        return static_cast<double>(*this) <=> value;
    }

    bool operator==(const Rational& other) const
    {
        return m_numerator * other.m_denominator == other.m_numerator * m_denominator;
    }

    bool operator==(double value) const
    {
        return static_cast<double>(*this) == value;
    }

    // -(a/b) = (-a)/b
    Rational operator-() const { return Rational{-m_numerator, m_denominator}; }

    // bool(a/b) = (a != 0)
    explicit operator bool() const { return m_numerator != 0; }

    // a     c     a*d + c*b
    // —— + —— = ———————————
    // b     d        b*d
    Rational& operator+=(const Rational& other)
    {
        m_numerator   = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
        m_denominator = m_denominator * other.m_denominator;
        return *this;
    }

    // a     c     a*d - c*b
    // —— - —— = ———————————
    // b     d        b*d
    Rational& operator-=(const Rational& other)
    {
        m_numerator   = m_numerator * other.m_denominator - other.m_numerator * m_denominator;
        m_denominator = m_denominator * other.m_denominator;
        return *this;
    }

    // a     c     a*c
    // —— * —— = ——————
    // b     d     b*d
    Rational& operator*=(const Rational& other)
    {
        m_numerator *= other.m_numerator;
        m_denominator *= other.m_denominator;
        return *this;
    }

    // a     c     a*d
    // —— / —— = ———————   除以分数 = 乘以倒数
    // b     d     b*c
    Rational& operator/=(const Rational& other)
    {
        m_numerator *= other.m_denominator;
        m_denominator *= other.m_numerator;
        return *this;
    }

    // ++(a/b) = a/b + 1 = (a + b) / b
    Rational& operator++()
    {
        m_numerator += m_denominator;
        return *this;
    }

    // (a/b)++  返回原值 a/b，自身变为 (a + b) / b
    const Rational operator++(int)
    {
        auto copy(*this);
        ++(*this);
        return copy;
    }

    // --(a/b) = a/b - 1 = (a - b) / b
    Rational& operator--()
    {
        m_numerator -= m_denominator;
        return *this;
    }

    const Rational operator--(int)
    {
        auto copy(*this);
        --(*this);
        return copy;
    }

private:
    int m_numerator, m_denominator;
};

export std::ostream& operator<<(std::ostream& stream, const Rational& r)
{
    return stream << r.getNumerator() << '/' << r.getDenominator();
}

export Rational operator+(const Rational& one, const Rational& other)
{
    auto copy{one};
    return copy += other;
}

export Rational operator-(const Rational& one, const Rational& other)
{
    auto copy{one};
    return copy -= other;
}

export Rational operator*(const Rational& one, const Rational& other)
{
    auto copy{one};
    return copy *= other;
}

export Rational operator/(const Rational& one, const Rational& other)
{
    auto copy{one};
    return copy /= other;
}