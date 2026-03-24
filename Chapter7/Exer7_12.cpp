// find()函数在子字符串内搜索
#include <iostream>
#include <string>

int main()
{
    std::string sentence{"Manners maketh man"};
    std::string word{"an"};
    int count{};

    for (size_t i{}; i <= sentence.length() - word.length();)
    {
        size_t position = sentence.find(word, i);
        if (position == std::string::npos)
        {
            break;
        }
        ++count;
        i = position + 1;
    }

    std::cout << '"' << word << "\" occurs in \"" << sentence
              << "\" " << count << " times." << std::endl;
}