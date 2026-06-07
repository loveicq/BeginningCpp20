/*************************第10章_练习_第3题************************
编写一个函数模板plus()，使其可接收两个不同类型的实参，返回这两个实参的和
。然后，确保可以使用plus()将两个给定指针指向的值相加。
附加题：读者是否能够修改plus()，使其也能够将两个字符串字面量连接起来？
注意，这可能没有想象中那样简单。
*****************************************************************/
#include <iostream>
#include <string>

template <typename T1, typename T2> auto plus(T1 *val1, T2 *val2)
{
  return *val1 + *val2;
}

template <typename T1, typename T2> auto plus(const T1 &val1, const T2 &val2)
// 直接传值方式，创建临时对象，必须用const来绑定，否则无法编译
{
  return val1 + val2;
}

std::string plus(const char *val1, const char *val2)
{
  return std::string{val1} + val2;
}

int main()
{
  double value1{10.5};
  int value2{5};
  std::cout << "With value1 = " << value1 << ", and value2 = " << value2
            << std::endl;
  std::cout << "plus(value1, value2) = " << plus(&value1, &value2) << std::endl;

  std::cout << "plus(3, 4.2) = " << plus(3, 4.2) << std::endl;

  std::string str1{"Hello,"}, str2{" world!"};
  std::cout << "\nWith str1 as \"" << str1 << "\" and str2 as \"" << str2 << '"'
            << std::endl;
  std::cout << "plus(str1,str2) = " << plus(str1, str2) << std::endl;

  std::string str{plus("ni", " hao!")};
  std::cout << "plus(\"ni\", \" hao!\") = " << str << std::endl;
}