/*************************第7章_练习_第2题************************
编写一个程序，读取包含任意行的文本字符串，查找并记录文本中所有不重复的
单词，记录每个单词出现的次数。输出各单词及其出现的次数。单词及其出现的
次数应在列中对齐。单词应该左对齐，次数应该右对齐。在表格的每一行中输出
3个单词。
*****************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <format>

int main()
{
    std::string text;
    std::vector<std::string> words;
    std::vector<size_t> counts;

    // 声明字母表变量，并存储52个大小写之母
    std::string letters;
    for (char c{'a'}; c <= 'z'; ++c)
        letters += c;
    for (char c{'A'}; c <= 'Z'; ++c)
        letters += c;

    std::cout << "请输入英文文本，以*号结尾：\n";
    std::getline(std::cin, text, '*');
    size_t start{text.find_first_of(letters)};
    while (start != std::string::npos)
    {
        size_t end{text.find_first_not_of(letters, start)};
        if (end == std::string::npos)
            end = text.length();
        std::string word{text.substr(start, end - start)};

        bool found{false};
        for (size_t i{}; i < words.size(); ++i)
        {
            if (word == words[i])
            {
                ++counts[i];
                found = true;
                break;
            }
        }
        if (!found)
        {
            words.push_back(word);
            counts.push_back(1);
        }

        start = text.find_first_of(letters, end + 1);
    }

    size_t maxLength{};
    for (auto &word : words)
        if (maxLength < word.length())
            maxLength = word.length();

    size_t maxCount{};
    for (auto &count : counts)
    {
        if (maxCount < std::to_string(count).length())
            maxCount = std::to_string(count).length();
    }

    const size_t perline{3};
    for (size_t i{}; i < words.size(); ++i)
    {
        std::cout << std::format("{:<{}} {:>{}}  ", words[i], maxLength, counts[i], maxCount);
        if ((i + 1) % perline == 0)
            std::cout << std::endl;
    }

    std::cout << std::endl;
}