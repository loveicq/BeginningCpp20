# 第3章 处理基本数据类型
## 3.1 运算符的优先级和相关性
知道运算优先级在哪查就行了
## 3.2 位运算符
位运算符一般用于不带符号的整型,常见应用是在整型变量中设置单个位,如开或关、男或女、真或假；也可以应用于颜色、字体等信息。
### 3.2.1 移位运算符
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
- 左移<<、右移>>、<<=、>>=
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

### 3.2.2 位模式下的逻辑运算

| 运算符 | 说明                                                              |
| :----: | :---------------------------------------------------------------- |
|   ~    | 按位求反运算符。反转操作数中的位，1变成0，0变成1                  |
|   &    | 按位与运算符。相应的位都是1,结果位就是1;否则就是0                 |
|   ^    | 按位与或运算符。相应的位不同,结果位就是1;相应的位相同,结果就是0   |
|   \|   | 按位或运算符。相应的位有一个是1,结果位就是1;两个位都是0,结果就是0 |

优先级如下:`~`➡`<<`、`>>`➡`&`➡`^`➡`|`

1. 使用按位与运算符
按位与运算符一般用于选择整数值中特定的一个位或一组位。
```cpp
#include <iostream>
#include <bitset> //用于bitset直接输出二进制

int main()
{
    using namespace std;

    unsigned short font{0x064C};
    unsigned short sizeMask{0x1F};
    unsigned short styleMask{0xFF00};
    unsigned short italicMask{0xFF3F};
    // 0x064C=ob0000'0110'0100'1100
    // 0x1F=0b0001'1111
    // 0xFF00=0b1111'1111'0000'0000
    // 0xFF3F=0b1111'1111'0011'1111
    // 从C++14开始，还可以直接使用二进制字面量赋值：unsigned short font {0b00000110'0'10'01100};

    auto size{static_cast<unsigned short>(font & sizeMask)};            // 求字号
    auto style{static_cast<unsigned short>((font & styleMask) >> 8)};   // 求字体
    auto non_italic‌{static_cast<unsigned short>(font & italicMask)};    // 关闭斜体位

    cout << "size = " << size << endl
         << "style = " << style << endl
         << "non_italic‌ = ob" << bitset<16>(non_italic‌) << endl;

    return 0;
}
```