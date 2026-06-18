// Implementation of the from_roman() function
// 模块实现单元（implementation unit）：`module roman;`
// 导入同一模块的内部分区 `internals`，以访问内部辅助函数。
// 该单元实现并由接口单元声明的 `from_roman(std::string_view)` 函数。
module roman;
import :internals;

unsigned int from_roman(std::string_view roman)
{
  unsigned int result{};
  for (size_t i{}, n{ roman.length() }; i < n; ++i)
  {
    const auto j{ from_roman(roman[i]) };   // Integer value of the i'th roman digit
    // Look at the next digit (if there is one) to know whether to add or subtract j
    if (i + 1 == n || j >= from_roman(roman[i + 1])) result += j; else result -= j;
  }
  return result;
}
