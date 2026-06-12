#include <iostream>

int global_var = 10;

int main()
{
    int global_var = 5; // 局部变量，和全局的同名

    // 直接用，访问的是局部的 global_var
    std::cout << global_var << std::endl; // 输出：5

    // 用 :: 前缀，访问的是全局的 global_var
    std::cout << ::global_var << std::endl; // 输出：10
}