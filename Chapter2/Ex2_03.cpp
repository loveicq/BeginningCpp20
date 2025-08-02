// Ex2_03.cpp
// Sizing a pond for happy fish
#include <iostream>
#include <cmath>
#include <numbers> //取π值

int main()
{
    const double fish_factor{2.0 / 6};

    double fish_count{};
    double fish_length{};

    std::cout << "Enter the number of fish you want to keep: ";
    std::cin >> fish_count;
    std::cout << "Enter the average fish length in inches: ";
    std::cin >> fish_length;
    std::cout << std::endl;

    const double pond_area{fish_count * fish_length * fish_factor};
    const double pond_diameter{2.0 * std::sqrt(pond_area / std::numbers::pi)};

    std::cout << "Pond diameter required for " << fish_count << " fish is "
              << pond_diameter << " feet." << std::endl;
    return 0;
}