// Exer11_04.cpp
/*************************第11章_练习_第4题************************
仍然将第2题的解决方案作为起点，将swap()和max_word_length()函数移动到
一个internals模块实现分区中。
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