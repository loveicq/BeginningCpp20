//Test7_02.cpp
#include<iostream>
#include<string>
#include<cctype>

int main()
{
    //定义并输入名字
    std::string first;
    std::string second;
    std::cout<<"Enter your first name: ";
    std::cin>>first;
    std::cout<<"Enter your second name: ";
    std::cin>>second;

    //定义句子并连接名字
    std::string sentence {"Your full name is "};
    sentence+=first+" "+second+".";

    //输出句子
    std::cout<<sentence<<std::endl;

    //用索引方式修改句子全部字母为大写
    for(size_t i{};i<sentence.length();++i)
    {
        sentence[i]=static_cast<char>(std::toupper(sentence[i]));
    }
    std::cout<<sentence<<std::endl;//YOUR FULL NAME IS PHIL MCCAVITY.

    //用基于范围for循环方式修改句子全部字母为小写
    for(char& ch:sentence)
    {
        ch=static_cast<char>(std::tolower(ch));
    }
    std::cout<<sentence<<std::endl;//your full name is phil mccavity.
}