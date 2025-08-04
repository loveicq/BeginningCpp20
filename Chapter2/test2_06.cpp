// 测试std::format()错误调试的try-catch块
#include <iostream>
#include <format>
#include <numbers>
#include <cmath>

int main()
{
    using namespace std;

    const double fish_factor{2.0 / 6};
    int fish_count{};
    double fish_length{};

    cout << "请输入鱼总数(条): ";
    cin >> fish_count;
    cout << "请输入鱼的平均长度(英寸): ";
    cin >> fish_length;
    cout << endl;

    double pond_area{fish_count * fish_length * fish_factor};
    double pond_radius{sqrt(pond_area / numbers::pi)};
    // cout << std::format(" 养 {:.2} 条鱼的池塘半径需要 {:.2f} 英尺。\n", fish_count, pond_radius);

    try
    {
        cout << format(" 养 {:.2} 条鱼的池塘半径需要 {:.2f} 英尺。\n", fish_count, pond_radius);
    }
    catch (const format_error &error)
    {
        cout << error.what() << '\n';
    }

    return 0;
}
