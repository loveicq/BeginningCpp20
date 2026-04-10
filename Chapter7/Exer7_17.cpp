// 字符串转换数字
#include <iostream>
#include <string>

int main()
{
    std::string s{"123"};
    int i{std::stoi(s)};

    std::cout << "The integer is " << i << '.' << std::endl;
}