/*************************第7章_练习_第9题************************
扩展第8题的方案，删除出现tautogram的首字母的所有地方（忽略大小写）。可
以采用简单的方式（还记得用来实现这种目的的库函数吗？），但也许采用困难
的方法，自己编写完整的代码更加有趣。
*****************************************************************/
#include <iostream>
#include <string>
#include <cctype>

int main()
{
    // 输入待检测的文本
    std::string text;
    std::cout << "请输入要检测的文本，以*号结尾：\n";
    std::getline(std::cin, text, '*');

    // 创建大小写字母表
    std::string alphabet;
    for (size_t c{'a'}; c <= 'z'; ++c)
        alphabet += c;
    for (size_t c{'A'}; c <= 'Z'; ++c)
        alphabet += c;

    // 查找首字母
    size_t firstLetterIndex{text.find_first_of(alphabet)};
    char firstLetter{};
    if (firstLetterIndex != std::string::npos)
    {
        firstLetter = tolower(text[firstLetterIndex]);
    }
    else
    {
        std::cout << "文本中不包含字母，程序即将退出！" << std::endl;
        return 0;
    }

    // 定位文本中的每个单词，并根据单词首字母判断是否tautogram
    bool ISTautogram{true};                // 先假设文本是tautogram
    auto wordStartIndex{firstLetterIndex}; // 第一个单词首字母的位置
    while (true)
    {
        size_t wordEndIndex{text.find_first_not_of(alphabet, wordStartIndex + 1)}; // 单词的末尾字母位置
        if (wordEndIndex == std::string::npos)
            wordEndIndex = text.length();
        wordStartIndex = text.find_first_of(alphabet, wordEndIndex + 1); // 其它单词首字母的位置
        if (wordStartIndex == std::string::npos)
            break;
        if (std::tolower(text[wordStartIndex]) != firstLetter)
            ISTautogram = false;
    }

    // 删除tautogram文本中所有与首字母相同的字符
    std::erase(text, std::tolower(firstLetter));
    std::erase(text, std::toupper(firstLetter));

    // 输出文本是否为tautogram
    if (ISTautogram)
    {
        std::cout << "输入的文本是tautogram。" << std::endl;
    }
    else
    {
        std::cout << "输入的文本不是tautogram。" << std::endl;
        return 0;
    }

    // 输出删除所有首字母后的文本
    std::cout << "删除所有首字母后的文本为："
              << text << std::endl;
}