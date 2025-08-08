// 测试format（参数索引）
#include <iostream>
#include <format>
using std::cout;
using std::endl;
using std::format;

int main()
{
    unsigned fish_count{20};
    double pond_radius{8.74039};

    cout << format("{1:.2f} feet is the radius required for a pond with {0} fishes.",
                   fish_count, pond_radius)
         << endl;
    cout << format("Default: {0}, binary: {0:#b}, hex.: {0:#x}", 314) << endl;

    return 0;
}