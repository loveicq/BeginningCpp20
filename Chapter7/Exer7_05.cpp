//Test7_04.cpp
//substr()函数获取子字符串,第二个实参超过string对象长度
#include<iostream>
#include<string>

int main()
{
    std::string phrase{"The higher the fewer."};
    std::string word1{phrase.substr(4,100)};

    std::cout<<word1<<std::endl;//higher the fewer.
}