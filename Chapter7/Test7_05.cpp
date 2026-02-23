// Test7_05.cpp
// 测试比较运算符
#include <iostream>
#include <string>
#include <cstring>

int main()
{
    const std::string word1{"age"};
    const std::string word2{"beauty"};
    const char word3[] = "cout";
    const char *word4{new char[5]};
    std::strcpy(const_cast<char *>(word4), "cout"); // 将字符串复制到动态分配的内存中

    // 比较两个string对象
    if (word1 < word2)
        std::cout << word1 << " comes before " << word2 << '.' << std::endl;
    else
        std::cout << word2 << " comes before " << word1 << '.' << std::endl;

    // 比较一个string对象和char[]字符串
    if (word2 < word3) // 只要有string对象参与比较，就重载了运算符，可以直接与char[]或char*
        std::cout << word2 << " is less than " << word3 << '.' << std::endl;
    else
        std::cout << word3 << " is less than " << word2 << '.' << std::endl;

    // 比较char[]字符串数组和char*字符串
    if (std::strcmp(word3, word4) < 0) // char*和char[]之间比较，不能用比较运算符，因为比较的是指针地址
        std::cout << word4 << " is greater than " << word3 << '.' << std::endl;
    else if (std::strcmp(word3, word4) > 0)
        std::cout << word3 << " is greater than " << word4 << '.' << std::endl;
    else
        std::cout << word3 << " is equal to " << word4 << '.' << std::endl;

    delete[] word4;
    word4 = nullptr;
}