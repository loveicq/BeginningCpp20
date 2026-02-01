#include <iostream>
#include <format>

int main()
{
    const size_t max{100};
    long primes[max]{2L};
    size_t count{1};
    long trial{3L};
    while (count < max)
    {
        bool isprime{true};
        for (size_t i{}; i < count && isprime; ++i)
        {
            isprime = trial % *(primes + i) > 0;
        }

        if (isprime)
        {
            *(primes + count++) = trial;
        }
        trial += 2;
    }

    std::cout << "The first " << max << " primes are:" << std::endl;
    for (size_t i{}; i < max; ++i)
    {
        std::cout << std::format("{:7}", *(primes + i));
        if ((i + 1) % 10 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}