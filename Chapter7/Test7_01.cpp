//Exer7_01.cpp
#include <iostream>
#include <string>

int main(){
    std::string first;
    std::string second;

    std::cout<<"Enter your first name: ";
    std::cin>>first;
    std::cout<<"Enter your second name: ";
    std::cin>>second;

    std::string sentence{"Your full name is "};
    sentence+=second;
    sentence+=','+' ';//此句会计算','和' '字符的ASCII码之和，再转换成字符（L）与sentence运算
    sentence+=first;

    std::cout<<sentence<<std::endl;//输出“McCavityLPhil”
    std::cout<<"The string contains "<<sentence.length()//只有31个字符
    <<" characters."<<std::endl;
}