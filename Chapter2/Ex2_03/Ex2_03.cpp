// Ex2_03.cpp
// Sizing a pond for happy fish
#include <cmath>
#include <iostream>
#include <numbers> //取π值

int main()
{
    const double fish_factor{2.0 / 6};
    // 一条典型的鱼（体长约 6 英寸）大约需要2方英尺的水面面积
    // fish_factor = 2.0 / 6 表达的就是这个"每英寸鱼需要多少面积"的换算系数。
    // 这个常数直接用"英寸的鱼"算出"平方英尺的池塘"，隐含地把单位跨越也打包进去了。

    double fish_count{};
    double fish_length{};

    std::cout << "Enter the number of fish you want to keep: ";
    std::cin >> fish_count;
    std::cout << "Enter the average fish length in inches: ";
    std::cin >> fish_length;
    std::cout << std::endl;

    const double pond_area{fish_count * fish_length * fish_factor};
    const double pond_diameter{2.0 * std::sqrt(pond_area / std::numbers::pi)};
    // A=πr²,A=π(d/2)²,A=π⋅(d²/2²)
    // 4A=πd²
    // 4A/π=d²
    // d=sqrt(4A/π)
    // d=sqrt(4)×sqrt(A/π)=2×sqrt(A/π)

    std::cout << "Pond diameter required for " << fish_count << " fish is "
              << pond_diameter << " feet." << std::endl;
}