// 第2章第1题
#include <iostream>
#include <format>

int main()
{

    using namespace std;

    unsigned inches{};
    unsigned feet{};
    unsigned inchesRemainder{};

    cout << "请输入整数值英寸数:";
    cin >> inches;
    feet = inches / 12;
    inchesRemainder = inches % 12;
    cout << format("{}英寸共有{}英尺{}英寸。\n", inches, feet, inchesRemainder);

    return 0;
}