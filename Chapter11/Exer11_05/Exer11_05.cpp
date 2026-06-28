// Exer11_05.cpp
/*************************第11章_练习_第5题************************
回到第1题的解决方案，但这一次不是像第2题那样创建实现文件，而是创建多个
接口分区文件，让每个分区文件仍然包含它们的函数定义。一个分区仍然包含所有
排序功能，另一个分区仍然包含剩余的实用工具(utils)。另外，重用第4题的
internals分区。
*****************************************************************/
import <string>;
import <iostream>;
import words;

int main()
{
    words::Words the_words;
    std::string text;
    const auto separators{" ,.!?\"\n"};

    std::cout << "Enter a string terminated by *:" << std::endl;
    getline(std::cin, text, '*');

    words::extract_words(the_words, text, separators);
    if (the_words.empty())
    {
        std::cout << "No words in text." << std::endl;
        return 0;
    }

    words::sort(the_words);
    words::show_words(the_words);
}