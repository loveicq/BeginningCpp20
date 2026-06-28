// Exer11_02.cpp
/*************************第11章_练习_第2题************************
对于第1题的解决方案，通过把所有函数定义移动到一个实现文件中，将模块的接口
与实现分开。在实现文件中，不要使用名称空间块。在练习时，将所有未导出的
函数从words名称空间中移出来，放到全局名称空间内，然后想清楚在导出单参数
sort()函数中如何仍然能够调用三参数的sort()函数。
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
    std::getline(std::cin, text, '*');

    words::extract_words(the_words, text, separators);
    if (the_words.empty())
    {
        std::cout << "No words in text." << std::endl;
        return 0;
    }

    words::sort(the_words);
    words::show_words(the_words);
}