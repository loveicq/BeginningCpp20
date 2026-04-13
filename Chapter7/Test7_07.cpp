// 使用compare()比较子字符串
#include <iostream>
#include <string>

int main()
{
    std::string word1{"A jackhammer"};
    std::string word2{"jack"};

    const int result{word1.compare(2, word2.length(), word2)};

    if (result == 0)
    {
        std::cout << word1 << " contains " << word2 << " starting at index 2" << std::endl;
    }
}