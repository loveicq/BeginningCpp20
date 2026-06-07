/*************************第10章_练习_第4题************************
编写自己的std::size()函数系列，命名为my_size()，使其不只可以处理固定
大小的数组，还可以处理std::vector<>和std::array<>对象。本练习不允许
使用sizeof()运算符。
*****************************************************************/
#include <array>
#include <iostream>
#include <vector>

template <typename T, size_t N> size_t my_size(const T (&array)[N])
{
  return N;
}

template <size_t N> size_t my_size(const char (&str)[N]) { return N - 1; }

template <typename T> size_t my_size(const std::vector<T> &vector)
{
  return vector.size();
}

template <typename T, size_t N> size_t my_size(const std::array<T, N> array)
{
  return N;
}

int main()
{
  int array[]{1, 2, 3, 4, 5, 6};
  std::cout << "Size of numbers is " << my_size(array) << std::endl;

  std::cout << "Size of life lesson is "
            << my_size("Always wear a smile. One size fits all.") << std::endl;

  std::vector<int> vector{1, 2, 3, 4, 5, 6};
  std::cout << "Size of vector is " << my_size(vector) << std::endl;

  std::array<int, 6> array_object{1, 2, 3, 4, 5, 6};
  std::cout << "Size of array is " << my_size(array_object) << std::endl;
}