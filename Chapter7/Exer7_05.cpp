/*************************第7章_练习_第5题************************
将第4题中的程序推而广之，使得决定两个字符串是否互为回文时，忽略空格。
在这个更广泛的定义中，认为funeral和real fun互为回文，eleven plus
two和twelve plus one互为回文，desperation和a rope ends it互为回文。
*****************************************************************/
#include <iostream>
#include <string>

int main()
{
    std::string word1, word2;
    std::cout << "请输入第一个字符串：";
    std::getline(std::cin, word1); // 包含空格，必须使用getline()
    std::cout << "请输入第二个字符串：";
    std::getline(std::cin, word2);

    for (int i{static_cast<int>(word1.length()) - 1}; i >= 0; --i)
    // 只能反向循环，防止下标改变会跳过元素或者访问越界
    // i必须由size_t转换成int，否则如果word1.length()=0时，结果-1会变成极大的正整数，访问越界
    {
        if (word1[i] == ' ')
            word1.erase(i, 1);
    }
    for (int i{static_cast<int>(word2.length()) - 1}; i >= 0; --i)
    {
        if (word2[i] == ' ')
            word2.erase(i, 1);
    }

    if (word1.length() != word2.length())
    {
        std::cout << "\"" << word1 << "\"与" << "\"" << word2 << "\"不是回文关系。\n";
        return 0;
    }

    std::string word2_copy{word2};
    for (char c : word1)
    {
        for (size_t i{}; i < word2_copy.length(); ++i)
            if (c == word2_copy[i])
            {
                word2_copy.erase(i, 1);
                break; // 防止把所有相同的字母都一次删除
            }
    }

    if (word2_copy.length() == 0)
        std::cout << "\"" << word1 << "\"与" << "\"" << word2 << "\"互为回文关系。\n";
    else
        std::cout << "\"" << word1 << "\"与" << "\"" << word2 << "\"不是回文关系。\n";

    // std::cout << "\"" << word1 << "\"与" << "\"" << word2 << "\"" << ((word2_copy.length() == 0) ? "互为" : "不是") << "回文关系。\n";
}