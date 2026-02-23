// Ex7_03.cpp
// Comparing strings
#include <iostream>
#include <string>
#include <format>
#include <vector>

int main()
{
    // 创建一个字符串向量来存储名字
    std::vector<std::string> names; // 因为是类类型，调用构造函数把内部状态置为空，有没有{}都是一样的
    std::string input_name;

    // 输入名字，直到用户输入空行
    for (;;)
    {
        std::cout << "输入名称,然后按Enter(空行停止): ";
        std::getline(std::cin, input_name);
        if (input_name.empty())
            break;
        names.push_back(input_name);
    }

    // 名字按字母顺序排序
    bool sorted{};
    do
    {
        sorted = true; // 假设已经排好序
        for (size_t i{1}; i < names.size(); ++i)
            if (names[i - 1] > names[i])
            {
                names[i].swap(names[i - 1]);
                sorted = false; // 如果有交换,则还未排好序
            }
    } while (!sorted); // 如果没排好序,为false;!false=true,继续循环

    // 找出最长名字的长度
    size_t max_length{};
    for (const auto &name : names)
        if (max_length < name.length())
            max_length = name.length();

    // 按每行5个名字输出
    const size_t field_width = max_length + 2;
    size_t count{};

    std::cout << "名字按字母先后排序:\n";
    for (const auto &name : names)
    {
        std::cout << std::format("{:>{}}", name, field_width); // 右对齐+动态宽度
        if (!(++count % 5))
            std::cout << std::endl;
    }

    std::cout << std::endl;
}