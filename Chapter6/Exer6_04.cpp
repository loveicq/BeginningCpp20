//Exer6_04.cpp
#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    size_t size{};
    std::cout<<"请输入数组大小：";
    std::cin>>size;
    std::vector<double> dataArr(size);
    double sum{};

    for(size_t n{};n<size;++n)
    {
        dataArr[n]=1.0/((n+1)*(n+1));
        sum+=dataArr[n];
    }

    double result{std::sqrt(sum*6)};
    std::cout<<"结果是："<<result<<"。"<<std::endl;
}