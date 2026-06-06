// Ex10_04.cpp
// 使用固定大小的数组实参的函数模板
#include <iostream>

template <typename T, size_t N> T average(const T (&array)[N]);

int main()
{
  double doubles[2]{1.0, 2.0};
  std::cout << average(doubles) << std::endl;

  double moreDoubles[]{1.0, 2.0, 3.0, 4.0};
  std::cout << average(moreDoubles) << std::endl;

  std::cout << average({1.0, 2.0, 3.0, 4.0}) << std::endl; // 有大括号

  int ints[]{1, 2, 3, 4};
  std::cout << average(ints) << std::endl;
}

template <typename T, size_t N> T average(const T (&array)[N])
{
  T sum{};
  for (size_t i{}; i < N; ++i)
    sum += array[i];
  return sum / N;
}