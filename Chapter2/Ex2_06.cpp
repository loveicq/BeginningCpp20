// Ex2_06.cpp
// Formatting numeric values with std::format()
#include <iostream>
#include <format>
#include <numbers>
using std::cout;
using std::endl;
using std::format;

int main()
{
    const double pi{std::numbers::pi};
    cout << format("default: {:.2},fixed:{:0.2f},scientific:{:.2e},"
                   "general:{:.2g}\n",
                   pi, pi, pi, pi);
    cout << format("default: {},binary:{:b},hex.:{:x}\n", 314, 314, 314);
    cout << format("default: {},decimal:{:d},hex.:{:x}\n", 'c', 'c', 'c'); // 字符'c'的ascii码为99
    cout << format("alternative hex.: {:#x},binary:{:#b},HEX.:{:#X}\n",
                   314, 314, 314);
    cout << format("forced sign: {:+},space sign:{: }\n", 314, 314);
    cout << format("all together: {:*<+10.4f},{:+#09x}\n", pi, 314);

    return 0;
}