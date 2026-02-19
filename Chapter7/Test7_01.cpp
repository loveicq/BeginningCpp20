//Test7_01.cpp
#include<iostream>
#include<string>
#include<numbers>
#include<format>

int main()
{
    const std::string result_string{"The result equals: "};
    double result{std::numbers::pi};
    
    std::cout<<result_string+std::to_string(result)<<std::endl;//The result equals: 3.141593

    std::string song_title{"Summer of '"};
    song_title+=std::to_string(69);
    std::cout<<song_title<<std::endl;//Summer of '69

    std::cout<<std::format("Summer of '{:x}\n",105);//Summer of '69(105的十六进制是69)

}