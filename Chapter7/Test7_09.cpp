// 利用compare()函数比较string对象子字符串和另一个string对象子字符串
#include <iostream>
#include <string>

int main()
{
    std::string text{"Peter Piper picked a peck of pickled peppers."};
    std::string phrase{"Got to pick a pocker or two."};

    for (size_t i{}; i < text.length() - 3; ++i) // or i<=text.length()-4;防止越界访问
    {
        if (text.compare(i, 4, phrase, 7, 4) == 0)
        {
            std::cout << "text contains " << phrase.substr(7, 4)
                      << " starting at index " << i << std::endl;
        }
    }
}