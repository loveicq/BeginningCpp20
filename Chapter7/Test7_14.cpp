// 练习find_last_of()函数
#include <iostream>
#include <string>

int main()
{
    std::string text{"Smith,where Jones had had \"had had\", had had \"had\"."
                     " \"Had had\" had had the examiners' approval."};
    std::cout << text.find_last_of("AaEeIiOoUu") << std::endl; // 输出91
}