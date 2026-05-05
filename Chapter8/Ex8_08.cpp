// Ex8_08.cpp
// 使用引用参数
#include <iostream>
#include <format>
#include <vector>
#include <string>

using std::string;
using std::vector;

void find_words(vector<string> &words, const string &str, const string &separators);
void list_words(const vector<string> &words);

int main()
{
    string text; // 要搜索的字符串
    std::cout << "Enter some text terminated by *:\n";
    std::getline(std::cin, text, '*');

    const string separators{" ,;:.\"!?'\n"}; // 单词分隔符
    vector<string> words;

    find_words(words, text, separators);
    list_words(words);
}

void find_words(vector<string> &words, const string &text, const string &separators)
{
    size_t start{text.find_first_not_of(separators)}; // 第一个单词的起始索引

    while (start != string::npos) // 查找单词
    {
        size_t end = text.find_first_of(separators, start + 1); // 查找单词的结尾
        if (end == string::npos)
            end = text.length();

        words.push_back(text.substr(start, end - start));    // 存储单词
        start = text.find_first_not_of(separators, end + 1); // 查找下一个单词的第一个字符
    }
}

void list_words(const vector<string> &words)
{
    std::cout << "Your string contains the following " << words.size() << " words:\n";
    size_t count{};
    for (const auto &word : words)
    {
        std::cout << std::format("{:>15}", word);
        if (!(++count % 5))
            std::cout << std::endl;
    }
    std::cout << std::endl;
}