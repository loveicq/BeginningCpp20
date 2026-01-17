#include <iostream>
#include <vector>

int main()
{
    std::vector<double> x;

    while (true)
    {
        double input{};
        std::cout << "Enter a non-zero value,or 0 to end: ";
        std::cin >> input;

        if (input == 0)
        {
            break;
        }

        x.push_back(input);
    }

    if (x.empty())
    {
        std::cout << "Nothing to sort..." << std::endl;
        return 0;
    }

    std::cout << "Starting sort." << std::endl;
    while (true)
    {
        bool swapped(false);

        for (size_t i{}; i < x.size() - 1; ++i) // x.size()-1是保证下面x[i+1]不会越界
        {
            if (x[i] > x[i + 1])
            {
                const auto temp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }

    std::cout << "Your data in ascending sequence:\n";
    const size_t perline{10};
    size_t n{};
    for (size_t i{}; i < x.size(); ++i)
    {
        std::cout << std::format("{:<8.1f}", x[i]);
        if (++n == perline)
        {
            std::cout << std::endl;
            n = 0;
        }
    }
    std::cout << std::endl;
}