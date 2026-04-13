// substr()函数提取string()对象子字符串
#include <iostream>
#include <string>

int main()
{
    std::string text{"Peter Piper picked a peck of pickled peppers."};
    std::string phrase{"Got to pick a pocket or two."};

    for (size_t i{}; i < text.length() - 3; ++i)
    {
        if (text.substr(i, 4) == phrase.substr(7, 4))
        {
            std::cout << "text contains " << phrase.substr(7, 4)
                      << " starting at index " << i << std::endl;
        }
    }
}