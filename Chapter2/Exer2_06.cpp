// 第6题
#include <iostream>
#include <format>
#include <numbers>

int main()
{
    using namespace std;

    const auto horLine{"------------------------------------------------------------"};

    cout << format("{:^60}\n", "表2-6 <numbers>模块中的数字常量示例");
    cout << format("{:^60}\n", horLine);
    cout << format("{:^19}|{:^19}|{:^20}\n", "常量", "描述", "近似值");
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.5f}...\n", "std:numbers::c", "自然对数的底", numbers::e);
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.5f}...\n", "std::numbers::pi", "π", numbers::pi);
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.5f}...\n", "std:numbers::sqrt2", "2的平方根", numbers::sqrt2);
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.3f}...\n", "std:numbers::phi", "黄金比例常量φ", numbers::phi);
    cout << format("{:^60}\n", horLine);

    return 0;
}