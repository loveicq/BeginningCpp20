//测试单引号定义string对象
#include <iostream>
int main()
{
    std::string singleChar = {'a'};
    std::cout<<"初始化的字符是"<<singleChar<<"。"<<std::endl;
    std::string proverb {"Many a mickle makes a muckle."};
    std::string my_string {proverb,7,6};
    std::cout<<"提取的字符串是："<<my_string<<"。\n";
}