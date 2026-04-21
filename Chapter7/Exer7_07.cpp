/*************************第7章_练习_第7题************************
创建一个程序，将用户输入的任意长度的整数序列计入一个string对象。该序列
中的数字由空格分隔，由#字符终止。用户在输入连续两个数字的时候，可以按
Enter键，也可以不按Enter键。接下来，从字符串中逐个提取所有数字。
*****************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <format>
int main()
{
    std::string digits;
    std::cout << "请输入一个整数序列，以#结尾：\n";
    std::getline(std::cin, digits, '#');

    std::vector<int> ints;
    long total{};
    size_t length{};
    size_t start{digits.find_first_of("-0123456789", 0)};
    for (; start != std::string::npos;)
    {
        std::string subStr;
        size_t end{digits.find_first_not_of("0123456789", start + 1)};
        if (end == std::string::npos)
            end = digits.length();
        subStr = digits.substr(start, end - start);
        if (length < subStr.length())
            length = subStr.length();
        if (subStr != "-")
        {
            ints.push_back(std::stoi(subStr));
            total += std::stoi(subStr);
        }
        start = digits.find_first_of("-0123456789", end + 1);
    }

    std::cout << std::format("这个整数序列共包含{}个整数，这些整数总和为{}。全部整数列举如下：\n", ints.size(), total);
    size_t i{};
    for (const int &num : ints)
    {
        ++i;
        std::cout << std::format("{:<{}}  ", num, length);
        if (i % 6 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}