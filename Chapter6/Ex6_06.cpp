#include <iostream>
#include <format>
#include <math.h>

int main()
{
    size_t max{};
    std::cout << "How many primes would you like? ";
    std::cin >> max;

    if (max == 0)
        return 0;

    auto *primes{new unsigned[max]};
    primes[0] = 2;
    size_t count{1};
    unsigned trial{3};

    while (count < max)
    {
        bool isprime{true};
        const auto limit{static_cast<unsigned>(std::sqrt(trial))};
        for (size_t i{}; primes[i] <= limit && isprime; ++i)
            isprime = trial % primes[i] > 0;
        if (isprime)
            primes[count++] = trial;
        trial += 2;
    }

    std::cout << "The first " << max << " primes are:" << std::endl;
    for (size_t i{}; i < max; ++i)
    {
        std::cout << std::format("{:7}", primes[i]);
        if ((i + 1) % 10 == 0) // primes[9]已经是第10个元素了,要换行,所以是i+1
            std::cout << std::endl;
    }
    std::cout << std::endl;

    delete[] primes;
    primes = nullptr;
}