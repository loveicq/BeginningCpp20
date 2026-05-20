/*************************第8章_练习_第2题************************
编写一个函数，要求读取字符串或字符数组作为输入，并反转它的顺序。使用什
么类型的参数最好？用main()函数测试该函数，提示用户输入一个字符串，反
转其顺序，再输出反转后的字符串。
注意：“反转其顺序”即指改变原字符串，所以需要用指针或引用，不能按值传递
*****************************************************************/
#include <iostream>
#include <string>
#include <format>

std::string reverse(std::string str);

int main()
{
    std::string sentence;

    std::cout << "Enter a sequence of characters, then press 'Enter': " << std::endl;
    std::getline(std::cin, sentence);
    std::cout << std::format("Your sequence in reverse order is:\n{}\n", reverse(sentence)) << std::endl;

    std::cout << "Here is a demonstration of reverse() working with a C-style string:" << std::endl;

    char stuff[]{"abcdefg"}; // C-style string
    std::cout << std::format("The original string is: \"{}\"\nReversed it becomes: \"{}\"",
                             stuff, reverse(stuff))
              << std::endl;
}
std::string reverse(std::string str)
{
    const size_t length{str.length()};
    for (size_t i{}; i < length / 2; ++i)
    {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
    return str;
}
