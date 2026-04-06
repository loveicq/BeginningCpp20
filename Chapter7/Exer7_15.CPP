// rfind()测试
#include <iostream>
#include <string>

int main()
{
    std::string sentence{"Manners maketh man"};
    std::string word{"an"};

    std::cout << sentence.rfind(word) << std::endl;  // 16 搜索string对象
    std::cout << sentence.rfind("man") << std::endl; // 15 搜索C样式字符串
    std::cout << sentence.rfind('e') << std::endl;   // 11 搜索字符,注意是单引号
}