/*************************第7章_练习_第3题************************
编写一个程序，从键盘上读取长度任意的文本字符串，再提示输入要在文本字符
串中查找的单词。程序应查找出现在文本字符串中的所有单词，不考虑大小写，
再用与单词中字符个数相同的星号替换该单词，然后输出新的文本字符串。注意
必须替换整个单词。例如，如果用户输入了字符串“Our house is your dis-
posal.”，要查找的单词是our，则得到的字符串应是“*** house is at your
 disposal.”，而不是“*** house is at y*** disposal.”。
*****************************************************************/
#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string text;
    std::string searchWord;

    std::cout << "请输入文本，以星号*结尾：\n";
    std::getline(std::cin, text, '*');
    std::cout << "请输入要替换的单词：";
    std::cin >> searchWord;

    // 将文本和要替换的单词全都转换成小写字母
    for (char &c : text)
    {
        if (std::isalpha(c))
            c = std::tolower(c);
    }

    for (char &c : searchWord)
    {
        if (std::isalpha(c))
            c = std::tolower(c);
    }

    size_t wordLength{searchWord.length()};
    std::string stars(wordLength, '*');
    size_t pos{};
    for (;;)
    {
        pos = text.find(searchWord, pos);
        if (pos == std::string::npos)
            break;
        bool startboundary{(pos == 0) || !(std::isalnum(text[pos - 1]))};
        bool endboundary{((pos + wordLength) == text.length()) || !(std::isalnum(text[pos + wordLength]))};
        if (startboundary && endboundary)
        {
            text.replace(pos, wordLength, stars);
            pos += wordLength;
        }
        else
        {
            ++pos;
        }
    }

    std::cout << "处理后的文本：\n"
              << text << std::endl;
}