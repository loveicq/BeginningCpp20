// Ex10_03.cpp
// auto自动推断返回函数模板实例化类型
#include <iostream>
// template <typename T1, typename T2>
// auto larger(const T1 &a, const T2 &b);
template <typename T1, typename T2>
auto larger(const T1 &a, const T2 &b) // 采用auto推断必须放到函数引用的位置之前
                                      // （本例为main函数之前），不能作为函数模板声明
{
    return a > b ? a : b; // 返回类型取决于 a > b 的结果！
}

int main()
{
    int small_int{10};
    std::cout << "Larger of " << small_int << " and 9.6 is "
              << larger(small_int, 9.6) << std::endl;

    std::string a_string{"A"};
    std::cout << "Larger of \"" << a_string << "\" and \"Z\" is \""
              << larger(a_string, "Z") << '"' << std::endl;
}