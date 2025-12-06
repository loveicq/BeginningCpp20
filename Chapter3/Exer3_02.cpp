#include <iostream>
#include <format>
int main()
{
    double shelfLength{};
    double shelfDepth{};
    std::cout << "请输入搁板的长度(英尺):";
    std::cin >> shelfLength;
    std::cout << "请输入搁板的深度(英尺):";
    std::cin >> shelfDepth;

    int boxSide{};
    std::cout << "请输入盒子的边长(英寸):";
    std::cin >> boxSide;

    const auto inchesPerFoot{12};

    auto boxes{static_cast<long>(shelfLength * inchesPerFoot / boxSide) * static_cast<long>(shelfDepth * inchesPerFoot / boxSide)};
    std::cout << std::format("一层搁板可以容纳{}个盒子。\n", boxes);

    return 0;
}