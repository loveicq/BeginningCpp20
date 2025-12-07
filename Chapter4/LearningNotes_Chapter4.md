# 第4章 决策
## 4.1 比较数据值
- 比较数据值
  - 关系运算符
  - 相等运算符
- bool值
  - true(非0值),(条件成立,真)
  - false(0),(条件不成立,假)
### 4.1.1 应用比较运算符
```cpp
#include <iostream>

int main()
{
    char first{};
    char second{};

    std::cout << "请输入一个字符:";
    std::cin >> first;
    std::cout << "请输入第二个字符:";
    std::cin >> second;

    std::cout << std::boolalpha; // 设置bool值显示为true和false,而非1和0。

    std::cout << "表达式 '" << first << " < " << second << "' 的值为"
              << (first < second) << "." << std::endl;
    std::cout << "表达式 '" << first << " == " << second << "'的值为 "
              << (first == second) << "." << std::endl;

    std::cout << std::noboolalpha; // 设置bool值显示为1和0,而非true和false。

/*
    使用下面的语句更简洁,还避免了运算符优先级的困扰:
    std::cout << std::format("表达式 '{} < {}' 的值为{}.\n", first, second, first < second);
    std::cout << std::format("表达式 '{} == {}' 的值为{}.\n", first, second, first == second);
*/
    return 0;
}
```
### 4.1.2 比较浮点数值
- NaN值既不小于、大于也不等于任何其他数字，甚至也不等于另一个NaN值
- ±Inf值，正、负无穷大
### 4.1.3 太空飞船运算符
<=>:三向比较运算符  
```cpp
#include <iostream>
#include <format>
#include <compare>

int main()
{
    std::cout << "请输入一个整数:";

    int value;
    std::cin >> value;

    std::strong_ordering ordering{value <=> 0};

    std::cout << std::format("value < 0:{}\n", ordering == std::strong_ordering::less);
    std::cout << std::format("value > 0:{}\n", ordering == std::strong_ordering::greater);
    std::cout << std::format("value == 0:{}\n", ordering == std::strong_ordering::equal);

    return 0;
}
```
1. 比较类型
    - strong_ordering（整数和指针）->less、greater、equal、equivalent
    - partial_ordering（浮点数）->less、greater、equivalent、unordered
    - weak_ordering（自定义）->less、greater、equivalent
2. 命名的比较函数（在`<compare>`中定义）
   - `std::is_lt()` 较小
   - `std::is_gt()` 较大
   - `std::is_eq()` 相等
   - `std::is_neq()` 不相等
   - `std::is_lteq()` 小于或等于
   - `std::is_gteq()` 大于或等于

