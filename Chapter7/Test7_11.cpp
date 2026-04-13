// 检查字符串的开始或结尾
#include <iostream>
#include <string>

int main()
{
    std::string text{"Start with the end in mind."};

    if (text.starts_with("Start"))
    {
        std::cout << "The text starts with 'Start'." << std::endl;
    }
    if (!text.ends_with("end"))
    {
        std::cout << "The text does not end with 'end'." << std::endl;
    }
}