/*************************第7章_练习_第6题************************
编写一个程序，从键盘上读取长度任意的文本字符串，再读取一个包含一个或多
个字母的字符串。输出文本字符串中以这些字母（大小写均可）开头的单词的完
整列表。
*****************************************************************/
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

int main()
{
    std::string text; // 待分离单词的文本
    std::string word; // 待搜索的文本
    std::cout << "请输入一个字符串,以*结尾：\n";
    std::getline(std::cin, text, '*');
    std::cout << "请输入要搜索的字符串：";
    std::cin >> word;

    std::vector<std::string> words;               // 存储分离的单词
    const std::string separators{" ,;:.\"!?'\n"}; // 单词分隔符
    size_t start{text.find_first_not_of(separators)};

    while (start != std::string::npos)
    {
        size_t end{text.find_first_of(separators, start + 1)};
        // 其实这里的start+1和后面的end+1，加不加1都不会影响结果的正确性，只是突出了代码的清晰度
        if (end == std::string::npos)
            end = text.length();
        words.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(separators, end + 1);
    }

    std::string lower_word;
    // 将待搜索的文本转换成小写
    for (char c : word)
        lower_word += tolower(c);

    // 输出包含待搜索的文本开头的单词
    for (const std::string &str : words) // &引用是原变量的别称,不是创建一个变量副本,如果不是引用就是创建一个副本
    {
        if (str.length() >= lower_word.length())
        {
            std::string lower_str;
            for (char c : str)
            {
                lower_str += tolower(c);
            }
            if (lower_str.compare(0, lower_word.length(), lower_word) == 0)
                std::cout << str << std::endl;
        }
    }
}
