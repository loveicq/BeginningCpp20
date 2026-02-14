// Exer6_06.cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

int main()
{
    size_t size{};
    std::cout<<"请输入数组大小：";
    std::cin>>size;
    auto dataArr{std::make_unique<std::vector<double>>(size)};
    double sum{};
    for(size_t n{};n<size;++n)
    {
        *((*dataArr).data() + n) = 1.0 / ((n + 1) * (n + 1));
        sum+=*(dataArr->data() + n);
    }

    double result{std::sqrt(sum*6)};
    std::cout<<"结果是："<<result<<"。"<<std::endl;
}