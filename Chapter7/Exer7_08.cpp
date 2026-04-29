/*************************第7章_练习_第8题************************
tautogram是一段文本，其中的所有单词都以相同的字母开始。在英语中，"tru-
ly tautograms triumph,trumpeting trills to trounce terrible trav-
esties."是tautogram的一个例子。要求用户输入一个字符串，然后检查该字符
串是不是tautogram（忽略大小写）。如果是，还要输出每个单词的开始字母。
注意：很难写出真正的tautogram，所以是不是可以放宽一下规则？也许可以允
许使用短单词把文本连接起来（如"a"、"to"、"is"、"are"等），或者只要求
有一定百分比的单词使用相同字母开头？读者可以自行尝试。
*****************************************************************/
#include <iostream>
#include <string>
#include <cctype>

int main()
{
    // 输入待检测是否tautogram的文本
    std::string text;
    std::cout << "请输入一段文本，以*号结尾：\n";
    std::getline(std::cin, text, '*');

    // 创建大、小写字母表
    std::string alphabet;
    for (char c{'a'}; c <= 'z'; ++c)
        alphabet += c;
    for (char c{'A'}; c <= 'Z'; ++c)
        alphabet += c;

    bool ISTautogram{true}; // 判断输入的文本是否tautogram

    size_t start{text.find_first_of(alphabet)}; // find_first_of()函数只有一个参数，默认从索引位置0开始查起
    if (start == std::string::npos)
    {
        std::cout << "输入文本无效，程序即将退出！" << std::endl;
        return 0;
    }

    char firstLetter = std::tolower(static_cast<unsigned char>(text[start])); // 得到第一个单词的首字母
    while (true)
    {
        size_t end{text.find_first_not_of(alphabet, start + 1)};
        if (end == std::string::npos)
            end = text.length();
        start = text.find_first_of(alphabet, end + 1);
        if (start == std::string::npos)
            break;
        if (std::tolower(static_cast<unsigned char>(text[start])) != firstLetter)
            ISTautogram = false;
    }

    std::cout << "这段文本" << (ISTautogram ? "是" : "不是") << "tautogram。" << std::endl;
}
