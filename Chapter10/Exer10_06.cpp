/*************************第10章_练习_第6题************************
第8章介绍了用于字符串指针的快速排序算法。扩展Ex8_17.cpp的实现，使其可用
于任何类型的vector(即存在<运算符的任何类型)。编写一个main()函数，使用该
算法对一些元素类型不同的vector进行排序，然后输出未排序的和排序后的元素
列表。自然，在实现这个程序时，还应该创建一个函数模板，可将任意元素类型
的vector流输出到std::cout。
*****************************************************************/
#include <format>
#include <iostream>
#include <vector>

template <typename T>
void swap(std::vector<T> &data, size_t first, size_t second);
template <typename T> void sord(std::vector<T> &data);
template <typename T> void sord(std::vector<T> &data, size_t start, size_t end);
template <typename T> void show(const std::vector<T> &data, size_t width = 5);

int main()
{
  std::vector<int> numbers{-2, 4, -5, 6, 10, -40, 56, 4, 67, 45};
  std::cout << show(numbers) << std::endl;
}

template <typename T> void show(const std::vector<T> &data, size_t width)
{
  const size_t data_per_line{80 / width - 1};
  // 传统终端默认80字符宽
  //- 1,预留一个字符位置（用于元素间的空格分隔）
  std::cout << std::format("{:{}}", data[0], width);

  size_t data_in_line{};
  for (size_t i{1}; i <= data.size(); ++i)
  {
    if (++data_in_line == data_per_line)
    {
      data_in_line = 0;
      std::cout << std::endl;
    }
    std::cout << std::format("{:{}}", data[i], width);
  }
  std::cout << std::endl;
}

template <typename T> void sort(std::vector<T> &data)
{
  if (!data.empty())
    sort(data, 0, data.size() - 1);
}

template <typename T> void sort(std::vector)