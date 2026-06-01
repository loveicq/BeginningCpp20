/*************************第9章_练习_第6题************************
假定有一个vector<>，它包含10个元素（或至少10个元素）。可以调用第5题中
的average10()函数来计算这10个元素（或前10个元素）的平均数吗？显然，不
能直接调用，但确实可以实现调用。毕竟，向量中已给出了所胡必需的数据（10
个连续的元素）。可以参阅标准库文档来寻求思路。
*****************************************************************/
#include <iostream>
#include <span>
#include <vector>

double average10(std::span<const double, 10> data);

int main()
{
    std::vector<double> values{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
                               11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0};
    std::span<const double, 10> values_first_10{values.data() + 10, 10};
    // 手动构造span（values.data()是data[0]的指针，+10是查看向量后10个元素）
    //参阅访问 cppreference.com，搜索std::span，可以得知first
    std::cout << "Average_values = " << average10(values_first_10) << std::endl;
}

double average10(std::span<const double, 10> data)
{
    double sum{};
    for (auto value : data)
        sum += value;

    return sum / data.size();
}