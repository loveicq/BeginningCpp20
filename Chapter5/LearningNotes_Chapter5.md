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