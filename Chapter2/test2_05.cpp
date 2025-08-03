// 格式化字符串setprecision()测试
#include <iostream>
#include <iomanip>
#include <numbers>
#include <cmath>

int main()
{
    using namespace std;
    const double fish_factor{2.0 / 6};
    int fish_count{};
    double fish_length{};

    cout << "请输入要养的鱼总数(条): ";
    cin >> fish_count;
    cout << "请输入要养的鱼的长度(英寸): ";
    cin >> fish_length;

    double pond_area{fish_factor * fish_count * fish_length};
    double pond_radius{sqrt(pond_area / numbers::pi)};

    cout << "鱼塘需要的半径是: "
         << setprecision(2) // 主要测试这个格式化字符串函数,保留两位小数
         << pond_radius << " 平方英尺。\n";

    return 0;
}