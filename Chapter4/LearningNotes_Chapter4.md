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
## 4.2 if语句
- 简单的if语句可以写在一行上
- 0会转换为`false`，其他非0值会转换为`true`
  
```cpp
#include <iostream>

int main()
{
    std::cout << "请输入一个50-100之间的整数：";

    int value{};
    std::cin >> value;

    if (value)
    {
        std::cout << "你输入的是一个非0数字。" << std::endl;
        return 0;
    }
    if (value < 50)
        std::cout << "输入无效！你输入的数字小于50！" << std::endl;
    if (value > 100)
        std::cout << "输入无效！你输入的数字大于100！" << std::endl;

    std::cout << "你输入的数字是" << value << "。" << std::endl;

    return 0;
}
```
### 4.2.1 嵌套的if语句
```cpp
#include <iostream>

int main()
{
    std::cout << "请输入一个字母:";

    char letter{};
    std::cin >> letter;

    if (letter >= 'A')
    {
        if (letter <= 'Z')
        {
            std::cout << "你输入的是大写字母。\n";
            return 0;
        }
    }

    if (letter >= 'a') // 此处少一对花括号，也是可以的。
        if (letter <= 'z')
        {
            std::cout << "你输入的是小写字母。\n";
            return 0;
        }

    std::cout << "你输入的不是字母。\n";

    return 0;
}
```
### 4.2.2 字符分类和转换
`<cctype>`头文件提供的字符分类函数
| 函数        | 所执行的动作                                                                                                 |
| :---------- | :----------------------------------------------------------------------------------------------------------- |
| isupper(c)  | 测试c是否是大写字母                                                                                          |
| islower(c)  | 测试c是否是小写字母                                                                                          |
| isalpha(c)  | 测试c是否是大写字母或小写字母（如果区域字母表包含其他字符，那么还要测试c是否既不是大写字母，也不是小写字母） |
| isdigit(c)  | 测试c是否是数字                                                                                              |
| isxdigit(c) | 测试c是否是十六进制数字，‘0’~‘9’、‘a’~‘f’或‘A’~‘F’                                                           |
| isalnum(c)  | 测试c是否是字母或数字                                                                                        |
| isspace(c)  | 测试c是否是空白                                                                                              |
| isblank(c)  | 测试c是否是空格字符                                                                                          |
| ispunct(c)  | 测试c是否是标点符号_{}[]#()<>%:;.?*+-/^&                                                                     | ~!=,\'" |
| isprint(c)  | 测试c是否是可打印字符                                                                                        |
| iscntrl(c)  | 测试c是否是不可打印字符，即控制字符                                                                          |
| isgraph(c)  | 测试c是否是图形字符，即除了空格之外的可打印字符                                                              |

`cctype`头文件提供的字符转换函数
| 函数       | 说明                                               |
| :--------- | :------------------------------------------------- |
| tolower(c) | 如果c是大写字母，就返回该字母的小写形式，否则返回c |
| toupper(c) | 如果c是小写字母，就返回该字母的大写形式，否则返回c |

```cpp
#include <iostream>
#include <cctype>

int main()
{
    std::cout << "请输入一个字母：";

    char letter;
    std::cin >> letter;

    if (std::isupper(letter))
    {
        std::cout << "你输入的是大写字母。\n";
        return 0;
    }

    if (std::islower(letter))
    {
        std::cout << "你输入的是小写字母。\n";
        return 0;
    }

    std::cout << "你输入的不是字母。\n";

    return 0;
}
```

yafasdfydfadsf大规模