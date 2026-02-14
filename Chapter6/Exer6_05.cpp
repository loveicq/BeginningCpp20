//Exer6_05.cpp
#include <iostream>
#include <cmath>
#include <memory>

int main()
{
    size_t size{};
    std::cout<<"请输入数组大小：";
    std::cin>>size;
    double sum{};
    auto dataArr{std::make_unique<double[]>(size)};

    for(size_t n{};n<size;++n)
    {
        // dataArr[n]=1.0/((n+1)*(n+1));
        *(dataArr.get()+n)=1.0/((n+1)*(n+1));
        // sum+=dataArr[n];
        sum+=*(dataArr.get()+n);
    }

    double result{std::sqrt(sum*6)};
    std::cout<<"结果是："<<result<<"。"<<std::endl;
}