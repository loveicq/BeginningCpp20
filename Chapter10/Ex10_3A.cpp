// Ex10_3A.cpp
#include <iostream>
#include <vector>
#include <string>

template <typename T1, typename T2>
decltype(auto) larger(const T1 &a, const T2 &b)
{
    return a > b ? a : b;
}

int main()
{
    const int small_int{10};
    std::cout << "Larger of " << small_int << " and 9.6 is "
              << larger(small_int, 9.6) << std::endl;

    const std::string a_string{"A"};
    std::cout << "Larger of \"" << a_string << "\" and \"Z\" is \""
              << larger(a_string, "Z") << '"' << std::endl;

    const std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
    std::cout << "The larger of our two vectors ends with "
              << larger(v1, v2).back(); // 返回const std::vector<int>&类型
}