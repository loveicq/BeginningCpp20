# 第5章 数组和循环
## 5.1 数组
- 数组是表示一系列内存空间的变量
- 数组的大小必须使用常量整数表达式来指定,最常用的是整数字面量,或是使用字面量进行初始化的const整形变量
- 数组第一个元素索引是0
- 编译器为数组分配连续的存储位置
- 定义数组时可以用初始化列表进行初始化`unsigned int height[6] {26,37,47,55,62,75};`.
  - 初始化列表中值的个数超过元素个数,不会编译;
  - 少于元素个数,没有提供初始值的元素就初始化为0;
  - 空的初始化列表把所有元素初始化为0.
- 要定义元素值不能被修改的数组,在类型前面加上关键字const.`const unsigned int height[6] {26,37,47,55,62,75};`
## 5.2 理解循环
- 将循环体执行一次称为一次迭代
- 循环形式
  - for
  - while
  - do-while
## 5.3 for循环
- `for(初始化;条件;迭代)`,for循环小括号内的所有表达式都可以省略,但分号必须有
- 注意size_t(无符号整数)的用法,一般用于索引记数,是个别名,可移植性好,适合各种平台编译
- 编译器不会检查数组索引是否有效,程序员需要自己确保引用的元素不会超出数组边界
## 5.4 避免幻数
使用const变量可以避免幻数(增加数组的元素个数,但忘记更改循环的次数)
```c++
#include <iostream>

int main()
{
    const unsigned size{6};
    unsigned height[size]{26, 37, 47, 55, 62, 75};

    unsigned total{};
    for (size_t i{}; i < size; ++i)
    {
        total += height[i];
    }

    const unsigned average{total / size};
    std::cout << "The average height is " << average << std::endl;

    unsigned count{};
    for (size_t i{}; i < size; ++i)
    {
        if (height[i] < average)
        {
            ++count;
        }
    }
    std::cout << count << " people are below average height." << std::endl;
}
```
## 5.5 用初始化列表定义数组的大小(此大小指元素个数,非内存占用大小)
在数组的定义中提供一个或多个初始值,就可以忽略数组的大小.元素的个数就是初始值的个数.例如:  
`int values[]{2,3,4};`等价于`int values[3]{2,3,4};`
## 5.6 确定数组的大小(此大小指元素个数,非内存占用大小)
1. 使用标准库的<array>模块中提供的std::size()函数  
  `int values[]{2,3,5,7,11,13,17,19,23,29};`  
  `std::size(values)`可得到数组的大小为10.
2. std::size()函数不只用于数组,还可以用来获得标准库定义的任何元素集合的大小,如std::vector<>和std::array<>容器
3. 使用sizeof运算符确定数组元素个数的方法:用数组的大小除以单个元素的大小即可.
```c++
#include <iostream>
#include <iterator> //为了可移植,应显式包含此头文件,而不是包含<array>,或者不包含(虽然在GCC15.1.0中不包含也可以编译通过)

int main()
{
    int values[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    std::cout << "There are " << std::size(values) << " elements in the array." << std::endl;

    auto sum{0};
    const size_t old_school_size = sizeof(values) / sizeof(values[0]);
    for (size_t i{}; i < old_school_size; ++i)
    {
        sum += values[i];
    }
    std::cout << "The array have " << old_school_size << " elements.\n"
              << "The sum of the array elements is " << sum << "." << std::endl;
}
```
4. C++17以后,应该用std::size()函数,而不是用sizeof()运算符
5. for循环可以在第三个循环控制表达式中累加元素的和  
  `auto sum{0};`  
  `for (size_t {}; i<std::size(values); sum += values[i++]);`  
  注意:  
     1. 上式中必须使用后缀++递增i,如果使用前缀++就会先递增i,计算结果将出错!
     2. 上式中行尾的单个分号是循环体的空语句!本例能够采用这种形式,是因为所有的计算都在循环控制表达式中完成了.
     3. 不推荐上式此种"简洁而聪明"的代码（在第三个控制表达式中计算）,而应该选择传统的、清晰的代码
## 5.7 用浮点数控制for循环
1. 使用浮点变量控制for循环时要小心小数部分的值可能不能用二进制浮点数准确地表示.
```c++
#include <iostream>
#include <format>
#include <numbers>

int main()
{
    const size_t values_per_line{3};
    size_t values_current_line{};
    for (double radius{0.2}; radius <= 3.0; radius += 0.2)
    {
        const auto area = std::numbers::pi * radius * radius;
        std::cout << std::format("radius = {:4.2f}, area = {:5.2f}; ", radius, area);
        if (++values_current_line == values_per_line)
        {
            std::cout << std::endl;
            values_current_line = 0;
        }
    }
    std::cout << std::endl;
}
```
2. 上面程序可学习的点:  
   - 使用values_per_line和values_current_line变量控制每行的数值数量,输出三句即输入回车,同时values_current_line归零
   - 不会再改变的变量,用const定义成常量
   - auto的使用
   - 注意++values_current_line的++放在不同位置,每行输出的值集数可能不同
   - format时,精准控制输出数值的宽度,同时注意使用空格保持输出数值的可读性
   - 🧨循环判断radius <= 3.0,但radius到2.8时就停止了,原因是下一轮radius结果比3.0略大,这是浮点数的二进制表示误差问题.如果非得使用浮点数进行判断,最经常和保险的做法是用容差判断.  
```c++
#include <iostream>
#include <format>
#include <numbers>

int main()
{
    const size_t values_per_line{3};
    size_t values_current_line{};

    //radius < 3.0 + 0.001; 容差判断
    for (double radius = 0.2; radius < 3.0 + 0.001; radius += 0.2)
    {
        const auto area = std::numbers::pi * radius * radius;
        std::cout << std::format("radius = {:4.2f}, area = {:5.2f}; ", radius, area);
        if (++values_current_line == values_per_line)
        {
            std::cout << std::endl;
            values_current_line = 0;
        }
    }
    std::cout << std::endl;
}
```
3. 任何数字,只要其分数部分的分母是奇数,就不能准确地表示为二进制浮点数(不能被2整除)
## 5.8 使用更复杂的for循环控制表达式
在第一个for循环控制表达式中定义并初始化多个给定类型的变量,变量之间用逗号隔开
```c++
#include <iostream>
#include <format>

int main()
{
    unsigned limit{};
    std::cout << "This program calculates n! and the sum of the integers "
              << "up to n for values 1 to limit.\n";
    std::cout << "What upper limit for n would you like? Input a integer:";
    std::cin >> limit;

    constexpr auto table_format = "{:>8} {:>8} {:>20}\n"; 
    //书中使用const auto编译错误,因为format()第一个参数要求必须是编译时常量,
    //而编译器不认为const是编译时常量.constexpr是强制编译时常量.

    std::cout << std::format(table_format, "integer", "sum", "factorial");

    for (unsigned long long n{1}, sum{}, factorial{1}; n <= limit; ++n)
    {
        sum += n;
        factorial *= n;
        std::cout << std::format(table_format, n, sum, factorial);
    }
}
```
**逗号运算符**  
- 逗号运算符是一个二元运算符,运算结果是其右操作数的结果
- 逗号运算符是左相关的,在所有的运算符中优先级最低
```c++
#include <iostream>

int main()
{
    auto i{1};
    auto value1{1};
    auto value2{1};
    auto value3{1};

    std::cout << "运算结果是:" << (value1 += ++i, value2 += ++i, value3 += ++i) << std::endl;
}
```
## 5.9 基于范围的for循环(C++20)
1. 基于范围的for循环的一般形式如下:  
    `for([initialization;] range_declaration : range_expression)`  
    `loop statement or block`  
    range_declaration标识了一个变量,它会被依次赋予范围中的每个值,在每次迭代时都会赋予一个新值.  
    例:  
    int values[]{2,3,5,7,11,13,17,19,23,29};  
    int total{};  
    for(int x:values)  
        total+=x;
2. auto关键字在基于范围的for循环中很常见.  
    for(auto x:values)  
        total+=x;
3. for循环内的x变量是局部变量,在循环外部不存在.不能通过修改x的值来修改values数组的元素.
## 5.10 while循环
```c++
#include <iostream>
#include <format>

int main()
{
    unsigned limit{};

    std::cout << "This program calculates n! and the sum of the integers "
              << "up to n for values 1 to limit.\n";
    std::cout << "What upper limit for n would you like? Input a ingeter less than 21: ";
    std::cin >> limit;

    constexpr auto table_format = "{:<8} {:<8} {:<20}\n";

    std::cout << std::format(table_format, "integer", "sum", "factorial");

    unsigned n{};
    unsigned sum{};
    unsigned long long factorial{1ULL};

    while (++n <= limit)
    {
        sum += n;
        factorial *= n;
        std::cout << std::format(table_format, n, sum, factorial);
    }
}
```
**for与while转换**
1. for
```c++
for (initialization; condition; iteration)
{
    body;
}
```
2. while
```c++
{
    initialization;  
    while (condition)  
    {
        body;  
        iteration;  
    }  
 }
 ```
 ## 5.11 do-while循环
