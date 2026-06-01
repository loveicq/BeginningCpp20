/*************************第9章_练习_第4题************************
无论何时阅读代码或编写代码，首先要考虑的一个问题是“如果……怎么办？”例如，
思考一下Ex9_03中的largest()函数，该函数先访问data[0]，但如果data为空
怎么办？针对这样的问题，有如下几种选择方案：
首先，可以添加代码注释，指明data不能为空。这称为设置先决条件
(precondition)。调用者违反先决条件会导致不确定的行为。若违背了先决条件，
那什么都玩法确定，正好Ellie Goulding的歌曲所言：一切皆可能发生(包括系统
崩溃)。
其次，可以对这样的边缘用例设计合理的行为。例如，设计一些结果，使函数为空
输入计算出这些结果。例如，对于空数组，让largest()函数返回非数值？
这两种选择方案有时候都是可行的，但按照本章的精神，还可以提出第三种方案吗？
*****************************************************************/
#include <iostream>
#include <string_view>
#include <optional>
#include <vector>
#include <array>
#include <string>

std::optional<double> largest(std::span<const double> data);
std::optional<int> largest(std::span<const int> data);
std::optional<std::string> largest(std::span<const std::string> words);
int main()
{
    const double array[]{1.5, 44.6, 13.7, 21.2, 6.7};//传统数组必须显式声明类型
    const std::vector numbers{15, 44, 13, 21, 6, 8, 5, 2};//容器可以自动推导类型
    const std::vector data{3.5, 5.0, 6.0, -1.2, 8.7, 6.4};//容器可以自动推导类型
    const std::array array_data{3.5, 5.0, 6.0, -1.2, 8.7, 6.4};//容器可以自动推导类型
    const std::vector<std::string> names{"Charles Dickens", "Emily Bronte",//此变量如果不显式声明，会推导为"const char*"类型
                                         "Jane Austen", "Henry James", "Arthur Miller"};
    std::cout << "The largest of array is " << *largest(array) << std::endl;
    std::cout << "The largest of numbers is " << largest(numbers).value() << std::endl;
    std::cout << "The largest of data is " << largest(data).value() << std::endl;
    std::cout << "The largest of array_data is (also) " << largest(array_data).value() << std::endl;
    std::cout << "The largest of names is " << largest(names).value_or("<null>") << std::endl;
}

std::optional<double> largest(std::span<const double> data)
{
    if (data.empty())
        return {};

    double maxValue{data[0]};
    for (auto value : data)
        if (maxValue < value)
            maxValue = value;

    return maxValue;
}

std::optional<int> largest(std::span<const int> data)
{
    if (data.empty())
        return {};

    int maxValue{};
    for (auto value : data)
        if (maxValue < value)
            maxValue = value;

    return maxValue;
}

std::optional<std::string> largest(std::span<const std::string> words)
{
    if (words.empty())
        return {};

    std::string maxWord{words[0]};
    for (const auto &word : words) // 注意，此处应是"const auto& word:words"引用
                                   // 而不是简单的"auto word:words"复制值
        if (maxWord < word)
            maxWord = word;

    return maxWord;
}
