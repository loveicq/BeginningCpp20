// Exer6_03.cpp
// 实际上是计算圆周率近似值
#include <iostream>
#include <cmath>
int main()
{
    size_t size{};
    std::cout<<"请输入数组大小:";
    std::cin>>size;
    double* dataArr{new double[size]{}};
    double sum{};
    for(size_t n{};n<size;++n)
    {
        *(dataArr+n)=1.0/((n+1)*(n+1));//必须写1.0，不能写1，否则精度不足，第一轮循环以后的结果总是0。
        sum+=*(dataArr+n);
    }
    double result{std::sqrt(sum*6)};
    std::cout<<"最终结果是:"<<result<<"。"<<std::endl;
    delete[] dataArr;
    dataArr=nullptr;
}