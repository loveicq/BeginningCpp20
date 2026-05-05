// Ex8_10.cpp
// Implicit conversions of reference parameters
#include <iostream>

void double_it(double it) { it *= 2; }
void print_it(const double &it) { std::cout << it << std::endl; }

int main()
{
    double d{123};
    double_it(d);
    print_it(d);

    int i{456};
    double_it(i);
    /*
    提示两条错误：
    1.cannot bind non-const lvalue reference of type 'double&' to a value of type 'int'
    2.无法用 "int" 类型的值初始化 "double &" 类型的引用(非常量限定)
    */
    print_it(i);
}