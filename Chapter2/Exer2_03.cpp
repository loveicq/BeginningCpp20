// 第3题
#include <iostream>
#include <cmath>
#include <numbers>

int main()
{
    using namespace std;

    const double inchesPerFoot{12.0};
    const double piDegrees{180.0};

    double feet{};
    double inches{};
    cout << "请分别输入你与树之间的距离是几英尺和几英寸(用空格隔开):";
    cin >> feet >> inches;
    const double distance{feet + inches / inchesPerFoot};

    double angle{}, angleToRadian{};
    cout << "请输入树顶的仰角（单位：度）:";
    cin >> angle;
    angleToRadian = angle * (numbers::pi / piDegrees); // 角度转换为弧度

    double eyeHeight{};
    cout << "请输入地面到眼睛的高度(英寸):";
    cin >> eyeHeight;
    eyeHeight /= inchesPerFoot;

    const double height{eyeHeight + distance * tan(angleToRadian)};                                   // 按公式计算树高度，这个三角函数要用弧度
    const unsigned heightFeet{static_cast<unsigned>(height)};                                         // 显式转换成无符号整数(英尺数)
    const unsigned heightInches{static_cast<unsigned>(round(inchesPerFoot * (height - heightFeet)))}; //(浮点数-整数)的余数乘12就是英寸数

    cout << "树的高度是" << heightFeet << "英尺"
         << heightInches << "英寸。" << endl;

    return 0;
}