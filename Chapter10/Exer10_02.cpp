/*************************第10章_练习_第2题************************
将Ex10_01中main()函数的最后几行修改如下：
const auto a_string = "A", z_string = "Z";
std::cout<<"Larger of "<<a_string<<" and "<<z_string
<<" is "<<larger(a_string, z_string)<<std::endl;
如果现在运行程序，很可能会得到如下输出（如果输出不同，则尝试改变a_string
和z_string的声明顺序）：
——————————————————————————————————————————————————————————————————
Larger of 1.5 and 2.5 is 2.5
Larger of 3.5 and 4.5 is 4.5
Larger of 17011983 and 10 is 17011983
Larger of A and Z is A
——————————————————————————————————————————————————————————————————
为什么"A"比"Z"大？读者能够解释这里发生了什么问题吗？是否能够修改该问题？
注意，要比较两个字符数组，可以先把它们转换为另一种字符串表示形式。
*****************************************************************/
#include <format>
#include <iostream>
#include <string>

template <typename T> T larger(T a, T b);
int main()
{
  std::cout << "Larger of 1.5 and 2.5 is " << larger(1.5, 2.5) << std::endl;
  std::cout << "Larger of 3.5 and 4.5 is " << larger(3.5, 4.5) << std::endl;

  int big_int{17011983}, small_int{10};
  std::cout << std::format("Larger of {} and {} is {}\n", big_int, small_int,
                           larger(big_int, small_int));

  //   const auto z_string = "Z", a_string = "a";
  // T 被推断为 const char*
  // a > b 比较的是指针地址，不是字符串内容！
  std::string z_string{"Z"}, a_string{"A"};
  std::cout << "Larger of " << a_string << " and " << z_string << " is "
            << larger(a_string, z_string) << std::endl;
}

// Template for functions to return the larger of two values
template <typename T> T larger(T a, T b) { return a > b ? a : b; }
