# 第3章 处理基本数据类型
## 3.1 运算符的优先级和相关性
知道运算优先级在哪查就行了
## 3.2 位运算符
```cpp
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