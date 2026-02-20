//Test7_03.cpp
//substr()函数获取子字符串
#include<iostream>
#include<string>

int main()
{
    std::string phrase{"The higher the fewer."};
    std::string word1{phrase.substr(4,6)};

    std::cout<<word1<<std::endl;//higher
}