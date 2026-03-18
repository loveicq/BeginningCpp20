// compare()函数搜索子字符串
#include <iostream>
#include <string>

int main()
{
    std::string text{"Peter Piper picked a peck of pickled peppers."};
    std::string word{"pick"};

    for (size_t i{}; i < text.length() - word.length() + 1; ++i) //+1是为了最少循环一次，假设text和word内容一样，也能正确输出结果（即包含，从索引0开始）
    {
        if (text.compare(i, word.length(), word) == 0)
        {
            std::cout << "text contains " << word << " starting at index " << i << std::endl;
        }
    }
}