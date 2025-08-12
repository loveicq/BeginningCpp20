// 第5题
#include <iostream>
#include <format>

int main()
{
    using namespace std;

    const double poundPerKg{2.2};
    const double footPerMeter{0.3048};
    const double inchesPerfoot{12};

    double weight{};
    cout << "请输入您的体重(磅):";
    cin >> weight;
    weight /= poundPerKg;

    double feet{};
    double inches{};
    double height{};
    cout << "请输入您的身高为几英尺几英寸(以空格分开输入):";
    cin >> feet >> inches;
    height = (feet + inches / inchesPerfoot) * footPerMeter;

    double BMI{};
    BMI = weight / (height * height);

    cout << format("您的BMI指数是{:.1f}\n", BMI);

    return 0;
}