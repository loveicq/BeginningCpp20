// 练习find_first_of()函数
#include <iostream>
#include <string>

int main()
{
    std::string text{"Smith,where Jones had had \"had had\",had had \"had \"."
                     " \"Had had\" had had the examiners' approval."};
    std::string separators{" ,.\""};
    std::cout << text.find_first_of(separators) << std::endl;
}