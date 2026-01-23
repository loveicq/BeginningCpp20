# 第6章 指针和引用
## 6.1 什么是指针
- 程序中每个变量和函数都位于内存的某个地方
- 指针是可存储地址的变量
  - `long* pnumber{};`//类型是"指向long"
  - 初始化列表为空,默认初始化为等价于0的指针,即不指向任何内容的地址,这种特殊的指针值写为nullptr,可显式地指定为初始值:`long* pnumber{nullptr};`
- 未初始化的指针很危险。应遵循的黄金规则:定义指针时，总是要初始化它。如果还不能为提供期望的值，就将其初始化为nullptr。
- 定义指针类型时，星号放在类型旁边或是变量名称旁边都可以
  - `long* pnumber{},number{};`//一个指针，一个普通变量
  - `long number{};long* pnumber{};`//一个指针，一个普通变量
  - `long *pnumber{},*number{};`//两个指针
- 同样的环境下，指针变量的大小是相同的：
  - 32bit:4byte
  - 64bit:8byte
```c++
#include <iostream>

int main()
{
    std::cout << sizeof(double) << " > " << sizeof(char16_t) << std::endl;
    std::cout << sizeof(double *) << " == " << sizeof(char16_t *) << std::endl;
}
```