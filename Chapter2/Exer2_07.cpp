// 第7题
#include <iostream>
#include <format>
#include <numbers>
#include <cmath>

int main()
{
    using namespace std;

    // 以下定义常量必须使用constexpr关键字,不能用const,不然会报错.原因是format()要求格式字符串必须为编译时常量.
    constexpr auto WIDTH60{"{:^60}\n"};
    const auto HORIZON{"------------------------------------------------------------"};
    constexpr auto HEADER_ALIGN_CENTER{"{:^19}|{:^19}|{:^20}\n"};
    constexpr auto DECIMAL_PRECISION_5{"{:<19}|{:<19}|{:.5f}...\n"};
    constexpr auto DECIMAL_PRECISION_3{"{:<19}|{:<19}|{:.3f}...\n"};
    constexpr auto SCIENTIFIC_NOTATION{"{:<19}|{:<19}|{:.5E}...\n"};

    cout << format(WIDTH60, "表2-6 <numbers>模块中的数字常量示例");
    cout << format(WIDTH60, HORIZON);
    cout << format(HEADER_ALIGN_CENTER, "常量", "描述", "近似值");
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_5, "std:numbers::c", "自然对数的底", numbers::e);
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_5, "std::numbers::pi", "π", numbers::pi);
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_5, "std:numbers::sqrt2", "2的平方根", numbers::sqrt2);
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_3, "std:numbers::phi", "黄金比例常量φ", numbers::phi);
    cout << format(WIDTH60, HORIZON);
    cout << format(SCIENTIFIC_NOTATION, "sin(π/4)", "科学记数法", sin(numbers::pi / 4));
    cout << format(WIDTH60, HORIZON);

    return 0;
}