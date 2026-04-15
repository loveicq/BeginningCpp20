/*************************第7章_练习_第4题************************
编写一个程序，提示输入两个单词，再测试它们，看看其中一个单词是否为另一
个单词的回文。通过重新排列一个单词中的字母，并只使用一次原字母，就构成
了原单词的回文。例如，listen和silent彼此互为回文，但是listens和
silent则不然。PS：只要单词字母数相等，字母频次相同即满足要求。
*****************************************************************/
#include <iostream>
#include <string>
#include <algorithm> //sort()
#include <format>

int main()
{
    std::string word1, word2;

    std::cout << "请输入第一个单词：";
    std::cin >> word1;
    std::cout << "请输入第二个单词：";
    std::cin >> word2;

    // 判断字母数是否相等
    if (word1.length() != word2.length())
    {
        std::cout << format("\"{}\"和\"{}\"不是回文关系。\n", word1, word2);
        return 0;
    }

    // 判断字母及频次是否相同
    std::sort(word1.begin(), word1.end());
    std::sort(word2.begin(), word2.end());
    if (word1 == word2)
        std::cout << std::format("\"{}\"和\"{}\"互为回文关系。\n", word1, word2);
    else
        std::cout << std::format("\"{}\"和\"{}\"不是回文关系。\n", word1, word2);
}