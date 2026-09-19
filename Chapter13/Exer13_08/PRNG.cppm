// PRNG.cppm
export module PRNG;

import <cstdint>;

export class PseudoRandomNumberGenerator
{
public:
    PseudoRandomNumberGenerator(int n = 0) : m_n{static_cast<uint64_t>(n % 100 + 100) % 100} {}

    int operator()()
    {
        m_n = (m_n * 41 + 7) % 100;
        return static_cast<int>(m_n);
    }

private:
    uint64_t m_n;
};