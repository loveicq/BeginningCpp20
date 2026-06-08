/*************************第10章_练习_第5题************************
读者是否能够想出一种方法，验证编译器对任何给定的实参类型，只生成函数模板
的一个实例？使用Ex10_01.cpp中的larger()函数进行测试。
*****************************************************************/
#include <format>
#include <iostream>
#include <string>

template <typename T> T larger(T a, T b);

int main()
{
  std::cout << "Larger of 3.5 and 2.5 is " << larger(3.5, 2.5) << std::endl;
  std::cout << "Larger of 5.6 and 10.6 is " << larger(5.6, 10.6) << std::endl;

  std::string a_string{"A"};
  std::string z_string{"Z"};
  std::cout << std::format(R"(Larger of "{}" and "{}" is "{}")", a_string,
                           z_string, larger(a_string, z_string));
}

template <typename T> T larger(T a, T b)
{
  static size_t counter{};
  std::cout << "(此实例化已被调用 " << ++counter << " 次)";
  return a > b ? a : b;
}