// Ex7_06.cpp
// Searching a string for characters from a set
#include <iostream>
#include <string>
#include <format>
#include <vector>

int main()
{
    std::string text;
    std::cout << "Enter som text terminated by *:\n";
    std::getline(std::cin, text, '*');

    const std::string separators{" ,;:.\"!?'\n"};
    std::vector<std::string> words;
    size_t start{text.find_first_not_of(separators)};

    while (start != std::string::npos)
    {
        size_t end = text.find_first_of(separators, start + 1);
        if (end == std::string::npos)
        {
            end = text.length(); // 最后一个词到末尾
        }
        words.push_back(text.substr(start, end - start));
        //"Hello,world!*",start=0,end=5,substr(0,5)-->Hello
        // "Hello,world!*",start=6,end=11,substr(6,5)-->world
        // "Hello,world!*",start=12,end=13,substr(12,1)-->*
        // "Hello,world!*",start=13,end=npos,substr(13,npos-13)-->""(空字符串)
        // 由于分隔符是" ,;:.\"!?'\n"，所以*也是分隔符，最后一个词是空字符串
        // 但是由于我们在寻找下一个词时使用了find_first_not_of(separators)，所以最后一个空字符串不会被添加到words中
        // 因此最终输出的单词只有"Hello"和"world"
        start = text.find_first_not_of(separators, end + 1);
    }

    std::cout << "Your string contains the following " << words.size() << " words:\n";
    size_t count{};
    for (const auto &word : words)
    {
        std::cout << std::format("{:15}", word);
        if (!(++count % 5))
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}