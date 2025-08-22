# 第3章 处理基本数据类型
## 3.1 运算符的优先级和相关性
知道运算优先级在哪查就行了
## 3.2 位运算符
```cpp
// 按位移动不带符号的整数示例
#include <iostream>

using namespace std;

int main()
{
    unsigned short number{16387};
    auto result{static_cast<unsigned short>(number << 2)};
    /*
    16387=0b0100000000000011
    0b0100000000000011 << 2 = 0b0000000000001100
    0b0000000000001100 = 12
    */
    cout << result << endl;

    return 0;
}
```
- <<、>>、<<=、>>=
- 在精度能满足的情况下，左移一位等于乘以2，右移一位等于除以2。
- 要注意位移舍弃有效位的情况，如上例。如果未使用stdtic_cast<>显式转换类型，则上例会隐式转换为signed int类型，结果就变成16387*4，而不是12了。
- 按位移动带符号的整数
  - 右移位:对于负数,会在左边空出来的位上填充1;对于正数,则填充0.不带符号的整数,符号位不扩充,在左边空出来的位上填充0.
  - 左移位:直接向左移动两位,在右边用0填充.左移操作可能改变整数的符号,如正变为负,负变为正.

```cpp
// 按位移动带符号的整数示例
#include <iostream>
#include <format>

int main()
{
    using namespace std;

    signed char positive{+104};
    signed char negative{-104};
    /*
    +104=0b01101000
    -104=0b10011000//01101000➡10010111(反码)➡10011000(补码)
    */
    cout << format("+104右移两位是{:+},-104右移两位是{:+}。\n",
                   static_cast<signed char>(positive >> 2),  //+26
                   static_cast<signed char>(negative >> 2)); //-26
    cout << format("+104左移两位是{:+},-104左移两位是{:+}。\n",
                   static_cast<signed char>(positive << 2),
                   // 原本应是+416，因char字节不足，舍弃前面两位，变成-96，符号也改变了
                   static_cast<signed char>(negative << 2));
    // 原本应是-416，因char字节不足，舍弃前面两位，变成+96，符号也改变了

    return 0;
}
```