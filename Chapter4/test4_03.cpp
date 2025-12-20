#include <iostream>

int main()
{
    int test{3};
    switch (test)
    {
        int i{1}; // switch正常执行必须是case语句,执行不到这一句
    case 1:
        int j{2};
        std::cout << test + j << std::endl;
        break;
        int k{3}; // 已经break了,这一句也永远不会执行
    case 3:
    { // 注意,case语句后有大括号,m的作用域仅限于此大括号内,初始化是合法的
        int m{4};
        std::cout << test + m << std::endl;
        break;
    }
    default:
        int n{5};
        std::cout << test + n << std::endl;
        break;
    }
    std::cout << j << std::endl; // 使用作用域外变量
    std::cout << n << std::endl; // 使用作用域外变量
}