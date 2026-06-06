/*************************第10章_练习_第1题************************
在C++17中，标准库的<algorithm>模块提供了方便的std::clamp()函数。表达式
clamp(a,b,c)用来将值a夹紧到闭区间[b,c]。即，如果a小于b，则表达式的结果
将为b；如果a大于c，则表达式的结果将为c；否则，如果a位于[b,c]区间内，
clamp()将返回a。编写自己的my_clamp()函数模板，并用一个小的测试程序测试
该函数模板。
*****************************************************************/
#include <iostream>

template <typename T> auto my_clamp(const T &a, const T &b, const T &c)
{
  if (a < b)
    return b;
  if (a > c)
    return c;
  return a;
}

int main()
{
  int a{}, b{}, c{};
  std::cout << "请输入a,b,c的值，以空格分开：";
  std::cin >> a >> b >> c;

  std::cout << "Clamp(" << a << ',' << b << ',' << c
            << ") = " << my_clamp(a, b, c) << std::endl;
}