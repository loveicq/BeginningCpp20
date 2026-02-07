// Ex6_07.cpp
#include <iostream>
#include <format>
#include <memory>
#include <vector>
#include <cctype>

int main()
{
    std::vector<std::shared_ptr<std::vector<double>>> records;
    size_t day{1};

    while (true)
    {
        auto day_records{std::make_shared<std::vector<double>>()};
        records.push_back(day_records);

        std::cout << "Enter the temperratures for day " << day++
                  << " separated by spaces.Enter 1000 to end:\n";

        while (true)
        {
            double t{};
            std::cin >> t;
            if (t == 1000.0)
                break;

            day_records->push_back(t);
        }

        std::cout << "Enter another day's tempertatures (Y or N)? ";
        char answer;
        std::cin >> answer;
        if (std::toupper(answer) != 'Y')
            break;
    }

    day = 1;

    for (auto record : records)
    {
        double total{};
        size_t count{};

        std::cout << std::format("\nTemperatures for day {}:\n", day++);
        for (auto temp : *record)
        {
            total += temp;
            std::cout << std::format("{:6.2f}", temp);
            if (++count % 5 == 0)
                std::cout << std::endl;
        }
        std::cout << std::format("\nAverage temperature: {:.2f}", total / count) << std::endl;
    }
}