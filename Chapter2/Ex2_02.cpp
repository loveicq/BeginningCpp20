// Ex2_02.cpp
// 此程序由于未考虑整数除法舍去小数问题,会发生前后输入和输出数据不一致的情况。如输入25 9 3。
#include <iostream>
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    unsigned yards{}, feet{}, inches{};
    cout << "请分别输入距离的码、英尺和英寸的数值,用空格分开:";
    cin >> yards >> feet >> inches;

    const unsigned feet_per_yard{3};
    const unsigned inches_per_foot{12};

    unsigned total_inches{};
    total_inches = yards * feet_per_yard * inches_per_foot + feet * inches_per_foot + inches;
    cout << "这个距离相当于" << total_inches << "英寸。" << endl;

    cout << "请输入一个距离(英寸):";
    cin >> total_inches;
    inches = total_inches % inches_per_foot;
    feet = total_inches / inches_per_foot;
    yards = feet / feet_per_yard;
    feet = feet % feet_per_yard;
    cout << "这个距离相当于" << yards << "码" << feet << "英尺" << inches << "英寸。\n";

    cin.get();
    return 0;
}