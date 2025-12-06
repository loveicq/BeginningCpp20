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
|   ^    | 按位异或运算符。相应的位不同,结果位就是1;相应的位相同,结果就是0   |
|   \|   | 按位或运算符。相应的位有一个是1,结果位就是1;两个位都是0,结果就是0 |

- 优先级如下:`~`➡`<<`、`>>`➡`&`➡`^`➡`|`
- 所有位运算符（~、&、|、^）都会进行整数提升,小于int的类型会被提升为int或unsigned int，所以书中案例都要显式转换static_cast\<unsigned short\>()

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
2. 使用按位或运算符
```cpp
#include <iostream>
#include <bitset>

int main()
{
    using namespace std;

    unsigned short font{0x064C};
    auto italic{0b1111'1111'1011'1111};
    auto bold{static_cast<unsigned short>(1u << 5)};
    // 1u=1 unsigned，常量，表示无符号整数1
    cout << "           font = " << bitset<16>(font) << endl
         << "fontCloseItalic = " << bitset<16>(font & italic) << endl
         << "   fontOpenBold = " << bitset<16>(font | bold) << endl;

    return 0;
}
```
学习两个表达式：
- font |= bold;
- font |= bold | italic; //'|'优先级比'|='高

3. 使用按位求反运算符
```cpp
#include <iostream>
#include <bitset>

int main()
{
    using namespace std;

    unsigned short font{0x064c};
    auto italic{static_cast<unsigned short>(1U << 6)};
    auto bold{static_cast<unsigned short>(1U << 5)};

    cout << "Initial font value: " << bitset<16>(font) << " (hex: 0x" << hex << font << dec << ")" << endl; // hex、dec,流控制符，先转十六进制输出，再转回十进制
    cout << "Italic bit mask:    " << bitset<16>(italic) << endl;
    cout << "Bold bit mask:      " << bitset<16>(bold) << endl
         << endl;

    // 关闭斜体
    unsigned short withoutItalic = font & ~italic;
    cout << "Without italic:     " << bitset<16>(withoutItalic) << endl;

    // 关闭粗体
    unsigned short withoutBold = font & ~bold;
    cout << "Without bold:       " << bitset<16>(withoutBold) << endl;

    // 关闭斜体和粗体
    unsigned short withoutBoth = font & ~(italic | bold);
    cout << "Without both:       " << bitset<16>(withoutBoth) << endl;

    // 另一种方式关闭斜体和粗体
    unsigned short withoutBoth2 = font & ~italic & ~bold;
    cout << "Without both (alt): " << bitset<16>(withoutBoth2) << endl;

    return 0;
}
```
4. 使用按位异或运算符
可以用来切换或反转单个位的状态
```cpp
#include <iostream>
#include <format>

int main()
{
    using namespace std;

    unsigned short font{0x064c};
    auto bold{static_cast<unsigned short>(1U << 5)};
    cout << format("     font = {:016b}\n     bold = {:016b}\n", font, bold);
    font ^= bold;
    cout << format("font^bold = {:016b}\n", font);

    return 0;
}
```
5. 使用按位运算符:一个示例
```cpp
#include <iostream>
#include <format>

int main()
{

    using namespace std;

    const unsigned int red{0xFF0000u};
    const unsigned int white{0xFFFFFFu};

    cout << "试验使用按位取反、与和或运算符:" << endl;
    cout << format("初始值:            red = {:08X}\n", red);
    cout << format("取反:             ~red = {:08X}\n", ~red);

    cout << format("初始值:          white = {:08X}\n", white);
    cout << format("取反:           ~white = {:08X}\n", ~white);

    cout << format("按位  AND: red & white = {:08X}\n", red & white);
    cout << format("接位   OR: red | white = {:08X}\n", red | white);
    cout << format("\n现在尝试连续进行异或运算:\n");

    unsigned int mask{red ^ white};
    cout << format("mask = red ^ white = {:08X}\n", mask);
    cout << format("        mask ^ red = {:08X}\n", mask ^ red);
    cout << format("      mask ^ white = {:08X}\n", mask ^ white);

    unsigned int flags{0xFF};
    unsigned int bit1mask{0x1};
    unsigned int bit6mask{0b100000};
    unsigned int bit20mask{1u << 19};

    cout << format("使用掩码来选择或设置特定的标志位:\n");
    cout << format("从标志位中选择第1位  : {:08X}\n", flags & bit1mask);
    cout << format("从标志位中选择第6位  : {:08X}\n", flags & bit6mask);
    cout << format("关闭标志位中的第6位  : {:08X}\n", flags &= ~bit6mask);
    cout << format("开启标志位中的第20位 : {:08X}\n", flags |= bit20mask);

    return 0;
}
```
- 设置位: value |= (1 << n);  
- 清除位: value &= ~(1 << n);  
- 翻转位: value ^= (1 << n);  
- 检查位: bit = value & (1 << n);

## 3.3 变量的生存期
- 变量的生存期
  - 局部变量.代码块中声明的非静态变量,在代码块结尾处消失.
  - 静态变量.static定义的变量,程序结束时消失.
  - 运行期间分配内存的变量.释放内存或销毁时消失.
  - thread_local声明的变量.
- 变量的作用域
  - 作用域是可以使用变量名访问的程序代码区域.

## 3.4 全局变量
- 没有初始化的全局变量,默认情况下被初始化为0
- 没有初始化的局部变量,默认情况下被初始化为垃圾值
- 如果有同名的全局变量和局部变量,变量名代表局部变量,如果要采用全局变量,需使用作用域解析运算符::限定它
- 如果把所有变量都声明为全局变量,会增加修改变量时出错的可能性,也会影响程序调试,同时增加内存消耗.
```cpp
#include <iostream>
long count1{999L};
double count2{3.14};
int count3;

int main()
{
    using namespace std;

    int count1{10};
    int count3{50};
    cout << "Value of outer count1 = " << count1 << endl;
    cout << "Value of global count1 = " << ::count1 << endl;
    cout << "Value of global count2 = " << count2 << endl;

    {
        int count1{20};
        int count2{30};
        cout << "\nValue of inner count1 = " << count1 << endl;
        cout << "Value of global count1 = " << ::count1 << endl;
        cout << "Value of inner count2 = " << count2 << endl;
        cout << "Value of global count2 = " << ::count2 << endl;

        count1 = ::count1 + 3;
        ++::count1;
        cout << "\nValue of inner count1 = " << count1 << endl;
        cout << "Value of global count1 = " << ::count1 << endl;
        count3 += count2;
        int count4{};//调试时提示"unused variable 'count4' [-Wunused-variable]"错误
    }
    // cout<<count4<<endl;//此句在编辑器显示"未定义标识符"错误
    cout << "\nValue of outer count1 = " << count1 << endl
         << "Value of outer count3 = " << count3 << endl; // 上面花括号也属于main()范围,所以count3是局部变量
    cout << "Value of global count3 = " << ::count3 << endl;

    cout << "Value of global count2 = " << count2 << endl; // count2局部变量定义在上面花括号内,作用域在右花括号处即结束了,所以此处是全局变量的count2.

    return 0;
}
```

## 3.5 枚举数据类型
1. 定义枚举类型
    - 传统枚举类型:`enum color{red,green,blue};`
    - 有作用域的枚举类型(C++11起):`enum class color{red,green,blue};`
2. 定义变量
    - 传统枚举变量:`color myColor=red;`
    - 有作用域的枚举变量:`color myColor{color::red};`
3. 输出枚举变量的值
    - 输出传统枚举变量值(直接输出):`cout<<myColor<<endl;`
    - 输出有作用域的枚举变量值(显式转换输出):`cout<<static_cast<int>(myColor)<<endl;`
4. 枚举成员的值
    - 第一个枚举成员的值默认是0,后面成员比前面成员的值大1
    - 枚举成员可以赋任何整数值
    - 枚举成员不一定有唯一值,不同成员可以赋同一个值
    - 枚举成员的值必须是编译期间的常量(字面量、以前定义的枚举成员、const变量)
    - 枚举成员可以是包含默认类型int在内的任何整数类型，也可以给所有的枚举成员显式赋值,用冒号隔开：  
`enum class Punctuation:char{Comma = ',',Exclamation = '!',Question = '?'};`

```cpp
#include <iostream>
#include <format>

int main()
{
    using namespace std;

    enum class Day
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };
    Day yesterday{Day::Monday}, today{Day::Tuesday}, tomorrow{Day::Wednesday};
    const Day poets_day{Day::Friday};
    enum class Punctuation : char
    {
        Comma = ',',
        Exclamation = '!',
        Question = '?'
    };
    Punctuation ch{Punctuation::Comma};
    cout << format("yesterday's value is {}{} but poets_day's is {}{}\n",
                   static_cast<int>(yesterday), static_cast<char>(ch),
                   static_cast<int>(poets_day), static_cast<char>(Punctuation::Exclamation));

    today = Day::Thursday;      // assign new...
    ch = Punctuation::Question; //...enumerator values
    tomorrow = poets_day;

    cout << format("Is today's value({}) the same as poets_day({}){}\n",
                   static_cast<int>(today), static_cast<int>(tomorrow), static_cast<char>(ch));
    // ch = tomorrow;     /*不能将 "Day" 类型的值分配到 "Punctuation" 类型的实体C/C++(513)*/
    // tomorrow = Friday; /*未定义标识符 "Friday"C/C++(20)*/
    // today = 6;         /*不能将 "int" 类型的值分配到 "Day" 类型的实体C/C++(513)*/

    return 0;
}
```
5. 可通过using enum声明绕过枚举类型名称指定为作用域,如`using enum Day`

## 3.6 数据类型的别名
使用using关键字指定类型别名  
`using BigOnes = unsigned long long`  
`using PhoneBook = std::map<std::shared_ptr<Contact>,std::string>`  
应有节制地使用类型别名

## 3.7 本章小结
 - 不需要记住所有的运算符的优先级和相关性,但在编写代码时需要考虑它们.如果不确定优先级就总是使用括号
 - 按位运算符作用也很重要
 - 理解局部变量(书中称自动变量)和全局变量,理解静态变量(static),理解变量生存期和作用域的概念
 - 枚举类型适合于表示固定的值集,尤其是有名称的值集
 - using关键字的用途

## 3.8 练习
1. 第1题
```
//第1题
#include <iostream>
#include <format>

int main()
{
    int originalInteger{};
    std::cout << "请输入一个整数:";
    std::cin >> originalInteger;
    const auto NOTInteger{static_cast<unsigned>(~originalInteger)};
    std::cout << std::format("{:#034b}|{:#034b}|{:#034b}\n",
                             originalInteger, NOTInteger,
                             NOTInteger + 1);
    std::cout << std::format("{:^34}|{:^34}|{:^34}\n",
                             originalInteger, ~originalInteger, ~originalInteger + 1);

    return 0;
}
```
2.第2题
```
// 第2题
#include <iostream>
#include <numbers>

int main()
{
    using namespace std;

    double radius{};
    double area{};

    cout << "请输入半径:";
    cin >> radius;
    area = numbers::pi * radius * radius;
    cout << "圆面积是" << area << "。" << endl;

    return 0;
}
```
3.第3题
```
// 第3题
#include <iostream>

int main()
{
    auto k{430u};
    auto j{(k >> 4) & ~(~0u << 3)};
    std::cout << j << std::endl;

    return 0;
}
```
4.第4题
```
// 第4题
#include <iostream>
#include <format>
#include <string>

// 函数：将整数格式化为二进制，每8位一组
std::string binary_with_separator(unsigned int value, int group_size = 8)
{
    const int total_bits = sizeof(value) * 8;
    std::string result;

    for (int i = total_bits - 1; i >= 0; i--)
    {
        result += (value >> i) & 1 ? '1' : '0';

        // 每 group_size 位添加分隔符（但不在开头和结尾）
        if (i > 0 && i % group_size == 0)
        {
            result += ' ';
        }
    }

    return result;
}

int main()
{
    unsigned packed{};
    unsigned char ch{};

    std::cout << std::format("{:16}", "请输入第1个字母:");
    std::cin >> ch;
    packed |= ch;
    packed <<= 8;

    std::cout << std::format("{:16}", "请输入第2个字母:");
    std::cin >> ch;
    packed |= ch;
    packed <<= 8;

    std::cout << std::format("{:16}", "请输入第3个字母:");
    std::cin >> ch;
    packed |= ch;
    packed <<= 8;

    std::cout << std::format("{:16}", "请输入第4个字母:");
    std::cin >> ch;
    packed |= ch;

    std::cout << "  这个字符串的二进制码是:0b" << binary_with_separator(packed, 8) << std::endl;
    std::cout << std::format("这个字符串的十六进制码是:{:#0x}\n", packed);

    unsigned int mask{0xff};

    std::cout << "      这个字符串反序输出:";

    ch = static_cast<char>(packed & mask);
    std::cout << ch;
    ch = static_cast<char>(packed >> 8 & mask);
    std::cout << ch;
    ch = static_cast<char>(packed >> 16 & mask);
    std::cout << ch;
    ch = static_cast<char>(packed >> 24 & mask);
    std::cout << ch << std::endl;

    return 0;
}
```
5.第5题
```
//第5题
#include <iostream>
#include <format>
#define formatString "{:^4}的三原色为:红:{:^3},绿:{:^3},蓝:{:^3}\n"

int main()
{
    enum class Color : unsigned
    {
        Red = 0xff0000u,
        Green = 0x00ff00u,
        Yellow = 0xffff00u,
        Purple = 0xff00ffu,
        Blue = 0x0000ffu,
        Black = 0x000000u,
        White = 0xffffffu
    };

    Color yellow{Color::Yellow};
    Color purple{Color::Purple};
    Color green{Color::Green};

    std::cout << std::format(formatString,
         "黄色",
         (static_cast<unsigned>(yellow) & static_cast<unsigned>(Color::Red)) >> 16,
         (static_cast<unsigned>(yellow) & static_cast<unsigned>(Color::Green)) >> 8,
         static_cast<unsigned>(yellow) & static_cast<unsigned>(Color::Blue));

    std::cout << std::format(formatString,
         "紫色",
         (static_cast<unsigned>(purple) & static_cast<unsigned>(Color::Red)) >> 16,
         (static_cast<unsigned>(purple) & static_cast<unsigned>(Color::Green)) >> 8,
         static_cast<unsigned>(purple) & static_cast<unsigned>(Color::Blue));

    std::cout << std::format(formatString,
         "绿色",
         (static_cast<unsigned>(green) & static_cast<unsigned>(Color::Red)) >> 16,
         (static_cast<unsigned>(green) & static_cast<unsigned>(Color::Green)) >> 8,
         static_cast<unsigned>(green) & static_cast<unsigned>(Color::Blue));

    return 0;
}
```
6.第6题
```
// 第6题
/*
异或^规律:
1.任何数与自己异或结果为0,即a^a=0;
2.任何数与0异或结果为自己,即a^0=a;
3.异或运算满足结合律和交换律,即a^b^c=a^(b^c),a^b=b^a;
*/

#include <iostream>

int main()
{
    int a{5};
    int b{10};

    std::cout << "交换前a = " << a << " , b = " << b << std::endl;

    a = a ^ b;
    b = a ^ b; // a展开,算式为b=(a^b)^b=a^0=a
    a = a ^ b; // a和b展开,算式为a=(a^b) ^ [(a^b)^b]=(a^a)^(b^b)^b=0^0^b=0^b=b

    std::cout << "交换后a = " << a << " , b = " << b << std::endl;

    return 0;
}
```