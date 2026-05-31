// Ex9_02.cpp
// Using std::string_view parameters
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <format>

void find_words(std::vector<std::string> &words,
                std::string_view text,
                std::string_view separators,
                size_t &maxStr);
void list_words(const std::vector<std::string> &words,
                const size_t maxStr);

int main()
{
    std::string text;
    std::cout << "请输入字符串，以*号结束：\n";
    std::getline(std::cin, text, '*');

    const std::string separators{" ,;:.\"!?'\n"};
    std::vector<std::string> words;
    size_t maxStr{}; // 最大的单词字符数
    find_words(words, text, separators, maxStr);
    list_words(words, maxStr);
}

void find_words(std::vector<std::string> &words,
                std::string_view text,
                std::string_view separators,
                size_t &maxStr)
{
    size_t start{text.find_first_not_of(separators)};

    while (start != std::string_view::npos)
    {
        size_t end{text.find_first_of(separators, start + 1)};
        if (end == std::string_view::npos)
            end = text.length();
        words.emplace_back(text.substr(start, end - start));
        if (maxStr < end - start)
            maxStr = end - start;
        start = text.find_first_not_of(separators, end + 1);
    }
}

void list_words(const std::vector<std::string> &words,
                const size_t maxStr)
{
    if (words.empty())
    {
        std::cout << "你未输入字符串，程序即将退出。" << std::endl;
        return;
    }

    size_t count{};
    std::cout << "\n字符串分解单词列举如下：\n";
    for (const auto &word : words)
    {
        std::cout << std::format("{:<{}}", word, maxStr + 1);
        if (++count % 5 == 0)
            std::cout << std::endl;
    }

    std::cout << std::endl;
}