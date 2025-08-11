// 第2题
#include <iostream>
#include <numbers>

int main()
{
    using namespace std;

    double radius{};
    double area{};

    cout << "请输入半径:";
    cin >> radius;
    area = numbers::pi * radius * radius;
    cout << "圆面积是" << area << "。" << endl;

    return 0;
}