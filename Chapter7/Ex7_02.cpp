//Ex7_02.cpp
//Accessing characters in a string
#include<iostream>
#include<cctype>
#include<string>

int main()
{
    //使用std::getline()输入字符串，包含空格字符
    std::string text;
    std::cout<<"Enter a line of text:\n";
    std::getline(std::cin,text);

    //统计字符串元音字符和辅音字符的数量
    unsigned vowels{};//元音数量
    unsigned consonants{};//辅音数量
    for(size_t i{};i<text.length();++i)
    {
        if(std::isalpha(text[i]))//判断是否为字母
        {
            switch (std::tolower(text[i]))
            {
            case 'a' :case 'e':case 'i':case 'o':case 'u':
                ++vowels;
                break;
            
            default:
                ++consonants;
                break;
            }
        }
    }

    //输出元音和辅音的数量
    std::cout<<"Your input contained "<<vowels<<" voewls and "
            <<consonants<<" consonants."<<std::endl;
}