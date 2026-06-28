// Exer11_03.cpp
/*************************第11章_练习_第3题************************
将第2题的words模块拆分为两个恰当命名的子模块：一个子模块包含所有排序
功能，另一个子模块包含剩余的实用工具（程序员常用utils表示实用工具）。
另外，将函数放到嵌套的名称空间中，其名称与子模块的名称对应。
*****************************************************************/
import words;
import <string>;
import <iostream>;

int main()
{
    words::Words the_words;
    std::string text;
    const auto separators{" ,.!?\"\n"};

    std::cout << "Enter a string terminated by *:" << std::endl;
    getline(std::cin, text, '*');

    words::utils::extract_words(the_words, text, separators);
    if (the_words.empty())
    {
        std::cout << "No words in text." << std::endl;
        return 0;
    }

    words::sorting::sort(the_words);
    words::utils::show_words(the_words);
}