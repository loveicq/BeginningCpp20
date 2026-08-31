# 第2章 基本数据类型

## 2.1 变量、数据和数据类型

### 2.1.1 定义整形变量

🈯定义:包含初始值的花括号称为`列表初始化`。  

```c++
int a = 4;       // 拷贝初始化（copy initialization）
int b(4);        // 直接初始化（direct initialization），书中称为函数初始化，不准确。不过此种初始化方式容易和函数定义混淆。
int c{4};        // 列表初始化（list initialization，C++11 引入）
int d = {4};     // 拷贝列表初始化（结合拷贝和列表语法）
```

- 实践只要使用列表初始化即可,其它方法熟悉,方便阅读其他代码。  
- 列表初始化允许使用表达式,但表达式应提前定义。  
- int类型一般为4字节,存储范围为-2147483648～+2147483647。  
- 初始化列表能够避免缩窄转换和以相同方式初始化所有变量，常被称为`统一初始化`。  

```c++
//Ex2_01.cpp
#include <iostream>
int main()
{
    int apple_count{15};
    int orange_count{5};
    int fruit_total{apple_count + orange_count};

    std::cout << "The value of apple_count is " << apple_count << std::endl;
    std::cout << "The value of orange_count is " << orange_count << std::endl;
    std::cout << "The value of fruit_count is " << fruit_total << std::endl;
}
```

以上程序运行结果如下：

---

```cpp
The value of apple_count is 15
The value of orange_count is 5
The value of fruit_count is 20 
```

---

|  类型名   | 类型的大小(字节) |                    值域                    |
| :-------: | :--------------: | :----------------------------------------: |
|   char    |        1         |                 -128～+127                 |
|   short   |        2         |                 -256～+255                 |
|    int    |        4         |          -2147483648～+2147483647          |
|   long    |       4或8       |            与int或long long相同            |
| long long |        8         | -9223372036854775808～+9223372036854775808 |

- signed:有符号整数(+、-),默认就是signed。单独的signed类型特指signed int。
- unsigned:无符号整数(+)。单独的unsigned类型特指unsigned int。
- char是不同于signed和unsigned的整数类型,不带修饰符一般只用于存储字符，如果要存储数字，必须带修饰符,或者用std::byte更合适(C++20)。

### 2.1.2 零初始化

- int counter {0}; 与int counter { };效果相同。
- 对于所有基本数值类型,空初始化列表总是被视为包含数字0。

### 2.1.3 定义有固定值的变量

- 使用const关键字,即定义常量。
- const unsigned toe_count {10};

## 2.2 整形字面量

### 2.2.1 十进制整形字面量

- 整数字面量：如123
- 浮点数字面量：如3.14
- 字符字面量：如'a'
- 字符串字面量：如"hello"
- 布尔字面量：如true/false
- 指针字面量：如nullptr
- 自定义字面量

字面量可以有后缀,如-123L、98U、12345ULL等，大小写不限，U和L前后不限。一般情况下实际编程不写后缀，但在某些情况下，  
需要添加正确的字面量后缀，例如初始化一个auto类型的变量或者调用有字面量实参的重载函数（第8章介绍）时。  
从C++14开始，可以使用单引号字符'使数值字面量更便于阅读,如22'333、-1'234LL、12'345ULL等。

### 2.2.2 十六进制整形字面量

- 十六进制整形字面量要加上0x或0X前缀。
- 十六进制整形字面量主要用于定义位的特定模式。例如下:
    - unsigned int color {0x0ff1ce};
    - int mask {0XFF00FF00};
    - unsigned long value {0xDEADlu};

### 2.2.3 八进制的整形字面量

- 八进制整形字面量要加前缀0。

### 2.2.4 二进制的整形字面量

- 二进制整形字面量要加前缀0b或0B。

```c++
// 这段代码测试不同进制整数的混合运算,结果表明c++会自动转换数制,并且前缀、后缀和分隔符不影响运算。
#include <iostream>
int main()
{
    //列表初始化时可以采用表达式,并且可以直接用不同数制的字面量整数
    long long finalResult{22'333uLL + 0xFF00FF00u + 0765321L + 0b110010101101U};
    std::cout << "22'333uLL + 0xFF00FF00u + 0765321L + 0b110010101101U = " 
                << finalResult << std::endl;
}
```

> 🤞`知识点`  在整形字面量中可以使用单引号作为分隔符,使字面量更容易阅读。包括十进制、十六进制和二进制的字面量，例如123'456'789、0xFF00'00FFu、0b11001010'11011001。

## 2.3 整数的计算

- 二元运算符:有两个操作数,如`+、-、*、/、%`等。
- 一元运算符:只有一个操作数,如`~`(取反运算)。
- 取模运算符%是对除法运算符/的补充：（x/y）*y +（x%y）= x。

> 👉`重点`  c++中整数除法结果总是整数,结果不会出现小数!

"/"或"%"的右操作数为0,后果很严重!除数为变量时,须编程人员主动防御(先判断被除数是否为0)。

|         场景         |        整数除法         |       浮点数除法       |
| :------------------: | :---------------------: | :--------------------: |
|      除数为常量0     |       编译报错 ❌       |      编译报错 ❌       |
|除数为变量（值为0）   | 编译通过 ✅运行崩溃 💥  |编译通过 ✅返回 inf/nan |

## 2.4 赋值运算

- "="是赋值运算符。
- 可以在单行语句中同时为多个变量赋值:a = b = c\*c - d\*d。

```c++
// Ex2_02.cpp
// 此程序由于未考虑整数除法舍去小数问题,会发生前后输入和输出数据不一致的情况。如输入25 9 3。
#include <iostream>
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    unsigned yards{}, feet{}, inches{};
    cout << "请分别输入距离的码、英尺和英寸的数值,用空格分开:";
    cin >> yards >> feet >> inches;

    const unsigned feet_per_yard{3};
    const unsigned inches_per_foot{12};

    unsigned total_inches{};
    total_inches = yards * feet_per_yard * inches_per_foot + feet 
                    * inches_per_foot + inches;
    cout << "这个距离相当于" << total_inches << "英寸。" << endl;

    cout << "请输入一个距离(英寸):";
    cin >> total_inches;
    inches = total_inches % inches_per_foot;
    feet = total_inches / inches_per_foot;
    yards = feet / feet_per_yard;
    feet = feet % feet_per_yard;
    cout << "这个距离相当于" << yards << "码" << feet << "英尺" << inches << "英寸。\n";
}
```

以上程序运行结果如下：

---

```cpp
请分别输入距离的码、英尺和英寸的数值,用空格分开:12 65 33
这个距离相当于1245英寸。
请输入一个距离(英寸):3
这个距离相当于0码0英尺3英寸。
```

---

**OP=赋值运算符**  
y += 1;

| 操作  | 运算符 |   操作   | 运算符 |
| :---: | :----: | :------: | :----: |
|  加   |   +=   |  按位与  |   &=   |
|  减   |   -=   |  按位或  |  \|=   |
|  乘   |   *=   | 按位异或 |   ^=   |
|  除   |   /=   | 向左移位 |  <<=   |
| 取模  |   %=   | 向右移位 |  >>=   |

## 2.5 sizeof运算符

使用`sizeof`运算符可以得到某类型、变量或表达式结果所占用的字节数。  

```c++
// 测试sizeof运算符
#include <iostream>
int main()
{
    int height{74};

    std::cout << "height变量占用" << sizeof height << "字节。" << std::endl;
    std::cout << "\"short\"数据类型占用" << sizeof(short) << "字节。" << std::endl;
    std::cout << "\"int\"数据类型占用" << sizeof(int) << "字节。" << std::endl;
    std::cout << "\"long long\"数据类型占用" << sizeof(long long) << "字节。" << std::endl;
    std::cout << "\"float\"数据类型占用" << sizeof(float) << "字节。" << std::endl;
    std::cout << "\"double\"数据类型占用" << sizeof(double) << "字节。" << std::endl;
    std::cout << "表达式\"height*height/2\"结果占用" << sizeof(height * height / 2) 
                << "字节。" << std::endl;
}
```

## 2.6 整数的递增和递减

- 一元运算符：递增`++`和递减`--`，前缀时优先级高于其它二元运算符。如：  
total = --count + 6;等效于下面两句：  
--count；  
total = count + 6;

```c++
count = count + 1;  
count += 1;  
++count;  
```

- 在使用++的后缀形式时,先在表达式中使用变量的值进行计算,再递增该变量的值.即后缀时优先级低于其它二元运算符。如：  
total = count-- + 6;等效于下面两句：
total = count + 6;  
--count;
- 一个语句只能对变量修改一次。类似`total = ++count * 3 + count ++ * 5;`这样赋值，其值是不能确定的。

## 2.7 定义浮点变量

|   数据类型  |            说明    | 精度(十进制位数) |           取值范围          |
| :---------: | :------:           | :-----:          | :--------------:            |
|   float     | 单精度浮点数       | 7                |   ±1.18×10⁻³⁸～±3.4×10³⁸    |
|  double     | 双精度浮点数       | 15(几乎16)       |  ±2.22×10⁻³⁰⁸～±1.8×10³⁰⁸   |
| long double | 扩展的双精度浮点数 |  18或19          | ±3.65×10⁻⁴⁹³²～±11.8×10⁴⁹³² |

> 👉`重点`  浮点数的精度是包含整数位和小数位的全部数字的（不包含小数点），所以要谨慎选择浮点数的数据类型。  
> 要注意理解精度和取值范围的含义。“大多数情况下，使用double类型就够了。通常，只有当速度或数据大小非常关键时，才会使用float。”  

📖`拓展阅读`  

---
一个浮点数在内存中通常由三部分组成（以最常见的32位float为例）：  

1. 符号位 (1 bit): 表示正负（0正，1负）。  
2. 指数部分 (8 bits): 决定数字的规模或范围（相当于科学计数法中的 10^N 的 N）。  
3. 尾数部分/有效数字部分 (23 bits): 决定数字的精度（相当于科学计数法中的 3.14159265 部分）。  
<!--   -->
**为什么float精度只有约7位，但范围有约10^38？**  

1. 精度（约7位有效数字）的来源：  
    - 这完全由尾数部分（23 bits） 决定。  
    - 23位二进制能精确表示的不同状态有 2²³ = 8,388,608 个。  
    - 8,388,608 大约是 10⁷（10,000,000）。这意味着尾数部分能区分大约 10⁷ 个不同的有效数字序列。  
    - 所以，float 能保证大约 7位十进制有效数字 是精确的。当你存储一个像 123456789.0f 的float时，
        它可能只能精确表示为 123456790.0 或 123456788.0（后几位不精确），因为有效数字超过了7位。
        但它能精确表示像 1.234567 或 12345.67 这样的数（只要总的有效数字不超过约7位）。  
1. 巨大范围（约 ±3.4e38）的来源：  
    - 这主要由指数部分（8 bits） 决定。  
    - 8位二进制能表示 256 个不同的指数值（通常用偏移码表示，实际指数范围大约是 -126 到 +127）。  
    - 指数的作用是 缩放 尾数部分表示的值。想象一下：  
        - 尾数部分能表示的最大值大约是 2 (二进制 1.111...1)。  
        - 当指数取最大值（约 +127)时，数字大小是 尾数最大值 × 2¹²⁷ ≈ 2 × 1.7e38 = 3.4e38。  
        - 当指数取最小值（约 -126)时，数字大小是 尾数最小值（约1) × 2⁻¹²⁶ ≈ 1.2e-38。  
    - 所以，指数部分赋予了浮点数跨越几十个数量级的能力。它决定了你能表示像 340, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000.0 (3.4e38) 这样巨大的数，也能表示像 0.000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 012 (1.2e-38) 这样微小的数。**指数部分不负责保证这些巨大或微小数字内部的有效数字有多精确，它只负责把尾数部分表示的小数点“浮动”到一个极其宽广的区间内。** 精度仍然只由那23位尾数决定。

---

## 2.8 浮点字面量

- float字面量加后缀f(或F)
- long long字面量加后缀L(或l)
- 没有后缀的浮点字面量是double类型
- 在浮点字面量中,指数是可选的,表示10的幂乘以该值.指数必须带有前缀e或E,其后是数值.如:5E3(5000.0)、100.5E2(10050.0)、2.5e-3(0.0025)、-0.1E-3L(-0.0001L)、.345e1F(=0.345*10<sup>1</sup>=3.45F).注意不要将这里的 e 与自然常数 e (≈2.71828) 混淆
- 编译器能够使用不带F或L后缀的字面量(甚至整形字面量)来初始化浮点变量.但是如果字面量的值超出了变量类型的可表示范围,编译器至少应该发出缩窄转换警告

## 2.9 浮点数的计算

- 浮点数的计算与整数计算相同
- 取模运算符%不能用于浮点操作数
- 可以使用 ++ 和 -- 运算符,变量会递增或递减1.0

### 2.91 数学常量

C++20提供了一个number模块

|        常量        |     描述     |   近似值   |
| :----------------: | :----------: | :--------: |
|   std::number::e   | 自然对数的底 | 2.71828... |
|  std::number::pi   |      π       | 3.14159... |
| std::number::sqrt2 |  2的平方根   | 1.41421... |
|  std::number::phi  | 黄金比例常量 |  1.618...  |

- 上表常量类型为double
- 如果需要float常量，应该使用std::number::pi_v\<float\>形式的表达式
- 如果需要long long常量，应该使用std::number::sqrt2_v\<long long\>形式的表达式
- 使用`预定义常量`要优于`自定义常量`

### 2.9.2 数学函数

- 使用标准头文件<cmath>
- 包含abs()、ceil()、floor()、exp()、log()（在计算机中表示以e为底的对数）、log10()、pow()、sqrt()、round()、lround()、llround()、cos()、sin()、tan()、acos()、asin()、atan()等数学函数
- 不能保证可将C头文件作为模块导入（import），而需要使用包含指令（#include）

```cpp
// Ex2_03.cpp
// Sizing a pond for happy fish
//书中案例程序把英寸转换成英尺,纯属是多余的步骤,还绕几圈,不便于理解
#include <iostream>
#include <cmath>
#include <numbers> //取π值

int main()
{
    const double fish_factor{2.0 / 6};

    double fish_count{};
    double fish_length{};

    std::cout << "Enter the number of fish you want to keep: ";
    std::cin >> fish_count;
    std::cout << "Enter the average fish length in inches: ";
    std::cin >> fish_length;
    std::cout << std::endl;

    const double pond_area{fish_count * fish_length * fish_factor};
    const double pond_diameter{2.0 * std::sqrt(pond_area / std::numbers::pi)}; 
    //pond_area=pi*(pond_diameter/2)²

    std::cout << "Pond diameter required for " << fish_count << " fish is "
              << pond_diameter << " feet." << std::endl;
    return 0;
}
```

### 2.9.3 无效的浮点效果

|      操作       |   结果    |        操作         | 结果  |
| :-------------: | :-------: | :-----------------: | :---: |
|    ±value/0     | ±infinity |         0/0         |  NaN  |
| ±infinity±value | ±infinity | ±infinity/±infinity |  NaN  |
| ±infinity*value | ±infinity |  infinity-infinity  |  NaN  |
| ±infinity/value | ±infinity |     infinity*0      |  NaN  |

- NaN:not a number; infinity:无穷
- 要验证数字是否inf或nan,应该使用`<cmath>`中的std::isinf()和std::()函数。

```cpp
// 本程序测试2.9.3节无限大、无限小数值和0的运算结果
#include <iostream>
int main()
{
    double a{1.5}, b{}, c{};
    double result{a / b};
    std::cout << a << "/" << b << "=" << result << std::endl;
    std::cout << result << "+" << a << "=" << result + a << std::endl;
    result = b / c;
    std::cout << b << "/" << c << "=" << result << std::endl;

    return 0;
}
```

`程序运行结果为：1.5/0=inf；  inf+1.5=inf；  0/0=nan`

### 2.9.4 缺点

- 一些小数值没有准确转换为二进制浮点数值。在计算过程中，很容易把一些小错误放大为大错误。
- 计算两个非常接近的数值之差会丧失精度。称为灾难性抵消。
- 处理范围相关几个数量级的数值会导致错误。如两个数相差10<sup>8</sup>倍，它们相加，较大值不会有变化。

## 2.10 混合的表达式和类型转换

- 隐式转换  
转换时会把低的转换成高的，排序如下：  
1.long double&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.unsigned long long&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.long  
2.double&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.long long&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8.unsigned int  
3.float&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6.unsigned long&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;9.int  
- 隐式转换可能会产生预料不到的结果
    - 下溢

    ```cpp
    unsigned int x{20u};
    int y{30};
    std::cout<<x-y<<std::endl;
    ```

    得出结果不是-10，而是4294967286
    - 上溢

    ```cpp
    unsigned char x{253};
    int y{5};
    std::cout<<x+y<<std::endl;
    ```

    得出结果不是258，而是2(258%256)
- 等号右边的表达式生成的值的类型不同于等号左边的变量类型时，编译器也会插入一个转换操作（缩窄转换）

    ```cpp
    int y{};
    double z{5.0};
    y=z;    //z转换成int类型再赋值给y
    ```

## 2.11 显式类型转换

- static_cast<转换后类型>(待转换的数值),如上节:y=static_cast\<int\>(z);
- 将浮点数强制转换为整数会进行截断，即丢弃浮点数的整个小数部分
- round()、lround()和llround()函数会将浮点数四舍五入到最接近的整数，大多情况下比强制转换更合适。
- 一般情况下，很少需要显式类型转换，特别是在数据为基本类型时。如果必须在代码中包含大量的显式强制转换，则通常表明应为变量选择更合适的类型。

```cpp
// Ex2_04.cpp
// Using explicit type conversions
#include <iostream>
int main()
{
    using namespace std;
    const unsigned feet_per_yard{3};
    const unsigned inches_per_foot{12};
    const unsigned inches_per_yard{feet_per_yard * inches_per_foot};
    double length{};
    unsigned int yards{};
    unsigned int feet{};
    unsigned int inches{};

    cout << "Enter a length in yards as a decimal: ";
    cin >> length;

    yards = static_cast<unsigned int>(length);
    feet = static_cast<unsigned int>((length - yards) * feet_per_yard);
    // 总英寸数与inches_per_foot取模（除以12取余数）即是英寸数，在此例中，英寸数总是小于12
    inches = static_cast<unsigned int>(length * inches_per_yard) % inches_per_foot;

    cout << length << " yards converts to "
         << yards << " yards "
         << feet << " feet "
         << inches << " inches." << endl;

    return 0;
}
```

- 旧式的强制转换  
C风格：`(转换后类型)待转换的数值`，这是C语言遗留下来的，现在应该使用C++风格的强制转换

## 2.12 格式化字符串

✅1. 使用\<iomanip\>模块

```cpp
    // 格式化字符串setprecision()测试
#include <iostream>
#include <iomanip>
#include <numbers>
#include <cmath>

int main()
{
    using namespace std;
    const double fish_factor{2.0 / 6};
    int fish_count{};
    double fish_length{};

    cout << "请输入要养的鱼总数(条): ";
    cin >> fish_count;
    cout << "请输入要养的鱼的长度(英寸): ";
    cin >> fish_length;

    double pond_area{fish_factor * fish_count * fish_length};
    double pond_radius{sqrt(pond_area / numbers::pi)};

    cout << "鱼塘需要的半径是: "
         << setprecision(2) // 主要测试这个格式化字符串函数,保留两位小数
         << pond_radius << " 英尺。\n";

    return 0;
}
```

✅2. 使用\<format\>模块(C++20才有这个模块)  
✅3. 使用std::format()格式化字符串  
    `std::cout<<std::format("pond radius required for {} fish is {} feet.\n",fish_count,pond_radius);`  
✅4. 格式说明符  
    - {:.2}点后面的数字指定总有效位数,包含小数点前和后的数字
    - {:.2f}加了f就是指定小数位数
    - 要调试失败的std::format()表达式,可以用try-catch块。实践中win10+vscode+gcc 15.1.0中这个try-catch块不能实现书中的错误诊断效果，还在语法检查阶段就报错了（如下例所示）。

```cpp
// 测试std::format()错误调试的try-catch块
#include <iostream>
#include <format>
#include <numbers>
#include <cmath>

int main()
{
    using namespace std;

    const double fish_factor{2.0 / 6};
    int fish_count{};
    double fish_length{};

    cout << "请输入鱼总数(条): ";
    cin >> fish_count;
    cout << "请输入鱼的平均长度(英寸): ";
    cin >> fish_length;
    cout << endl;

    double pond_area{fish_count * fish_length * fish_factor};
    double pond_radius{sqrt(pond_area / numbers::pi)};
    // cout << std::format(" 养 {:.2} 条鱼的池塘半径需要 {:.2f} 英尺。\n", fish_count, pond_radius);

    try
    {
        cout << format(" 养 {:.2} 条鱼的池塘半径需要 {:.2f} 英尺。\n", fish_count, pond_radius);
    }
    catch (const format_error &error)
    {
        cout << error.what() << '\n';
    }

    return 0;
}
```

![try_catch测试](https://tc.z.wiki/autoupload/f/9lpqiNvEAS8uNqygSEXEG7KXl_QqVl-bpSwqP4fJO68/20250804/EJRf/1444X363/try_catch.png)

1. `[fill][align][sign][#][0][width][.precision][type]`,可选的格式化选项
    - fill：填充字符,默认是空格,必须在align前面，指定空白处的填充字符
    - align：对齐方式,默认是右对齐
      - <：左对齐
      - \>：右对齐
      - ^：居中对齐
    - sign：符号控制,默认是显示正负号，仅用于数值类型
      - +：强制显示正负号（+3.14, -42）
      - -：仅负数显示符号（默认，3.14, -42）
      - 空格：正数前加空格，负数前加负号（" 3.14", "-42"）
    - #：替代形式，仅用于数值类型
      - 整数：为二进制（0b）、八进制（0）、十六进制（0x）添加前缀
      - 浮点数：强制显示小数点（即使无小数部分）
    - 0：零填充，仅用于数值类型。如果是整数,则用0填充;如果是浮点数,则显示小数点
    - width：字段宽度
      - 指定输出的最小字符数，不足则用填充字符补齐
      - 若实际内容长于width，则按实际长度输出（不截断）
    - .precision：精度，依类型而异
      - 浮点数：指定小数部分的位数（四舍五入）
      - 字符串：指定最大输出长度（截断超出部分）
      - 整数：无效（使用会导致编译错误）
    - type：数据类型，决定如何解析参数
      - 浮点数类型：
        - f：固定点表示（如3.14）
        - e/E：科学计数法（如3.14e+00）
        - g/G：自动选择f或e（默认）
      - 整数类型：
        - d/i：十进制
        - b：二进制
        - o：八进制
        - x/X：十六进制（小写/大写）
      - 其他类型：
        - s：字符串
        - c：字符
        - p：指针地址
        - 布尔值：true/false

✅6. 格式化表格式数据  
主要介绍width\alignment\fill\0等格式化选项，详细解释见第5点。  

```cpp
// Ex2_05.cpp
//  The width,alignment,fill,and 0 formatting options of format()
#include <iostream>
#include <format>
using std::cout;
using std::format;

int main()
{
    // Default alignment:right for numbers,left otherwise
    cout << format("{:7}|{:7}|{:7}|{:7}|{:7}\n", 1, -0.2, "str", 'c', true);
    // left and right alignment + custom fill character
    cout << format("{:*<7}|{:*<7}|{:*>7}|{:*>7}|{:*>7}\n", 1, -0.2, "str", 'c', true);
    // centered alignment +0 formatting option for numbers
    cout << format("{:0^7}|{:0^7}|{:^7}|{:^7}|{:^7}\n", 1, -0.2, "str", 'c', true);

    return 0;
}
```

上面的程序运行结果如下：

<img src=<https://z.wiki/u/J78qrS>>

✅7. 格式化数字  
主要介绍sign\\#\.precision\type等格式化选项，详细解释见第5点。

```cpp
// Ex2_06.cpp
// Formatting numeric values with std::format()
#include <iostream>
#include <format>
#include <numbers>
using std::cout;
using std::endl;
using std::format;

int main()
{
    const double pi{std::numbers::pi};
    cout << format("default: {:.2},fixed:{:0.2f},scientific:{:.2e},"
                   "general:{:.2g}\n",
                   pi, pi, pi, pi);
    cout << format("default: {},binary:{:b},hex.:{:x}\n", 314, 314, 314);
    cout << format("default: {},decimal:{:d},hex.:{:x}\n", 'c', 'c', 'c'); // 字符'c'的ascii码为99
    cout << format("alternative hex.: {:#x},binary:{:#b},HEX.:{:#X}\n",//在g++15.1.0中“{:#X}”也是小写
                   314, 314, 314);
    cout << format("forced sign: {:+},space sign:{: }\n", 314, 314);
    cout << format("all together: {:*<+10.4f},{:+#09x}\n", pi, 314);

    return 0;
}
```

上面的程序运行结果如下：
<img src=<https://z.wiki/u/9HwRnn>>

✅8. 参数索引  

```cpp
// 测试format（参数索引）
#include <iostream>
#include <format>
using std::cout;
using std::endl;
using std::format;

int main()
{
    unsigned fish_count{20};
    double pond_radius{8.74039};

    cout << format("{1:.2f} feet is the radius required for a pond with {0} fishes.",
                   fish_count, pond_radius)
         << endl;
    cout << format("Default: {0}, binary: {0:#b}, hex.: {0:#x}", 314) << endl;

    return 0;
}
```

👉注意：

- 参数索引从0开始
- 参数索引可以重复使用
- 参数索引可以不连续

## 2.13 确定数值的上下限

使用`numeric_limits<type_name>::min()`、`numeric_limits<type_name>::lowest()`和`numeric_limits<type_name>::max()`读取基本数据类型的上下限。

```cpp
// Ex2_07.cpp
// Finding maximum and minimum values for data types
#include <iostream>
#include <format>
#include <limits>
using std::cout;
using std::endl;
using std::format;
using std::numeric_limits;

int main()
{
    cout << format("The range for type short is from {} to {}\n",
                   numeric_limits<short>::min(), numeric_limits<short>::max())
         << format("The range for type unsigned int is from {} to {}\n",
                   numeric_limits<unsigned int>::min(), numeric_limits<unsigned int>::max())
         << format("The range for type long is from {} to {}\n",
                   numeric_limits<long>::min(), numeric_limits<long>::max())
         << format("The range for type float is from {} to {}\n",
                   numeric_limits<float>::min(), numeric_limits<float>::max())
         << format("The range for type float is from {} to {}\n",
                   numeric_limits<float>::lowest(), numeric_limits<float>::max())
         << format("The range for type double is from {} to {}\n",
                   numeric_limits<double>::min(), numeric_limits<double>::max())
         << format("The range for type double is from {} to {}\n",
                   numeric_limits<double>::lowest(), numeric_limits<double>::max())
         << format("The range for type long double is from {} to {}\n",
                   numeric_limits<long double>::min(), numeric_limits<long double>::max())
         << format("The range for type long double is from {} to {}\n",
                   numeric_limits<long double>::lowest(), numeric_limits<long double>::max());

    return 0;
}
```

上面程序的运行结果如下，注意浮点数min()和lowest()的区别：  
<img src="https://z.wiki/u/hRSubG">  

确定基本类型的其他属性  

- 返回二进制数字的位数：  
  `std::numeric_limits<type_name>::digits;`
- 获得infinity的浮点值(正无穷大)：  
  `float positive_infinity=std::numeric_limits<float>::infinity();`
- 获得infinity的浮点值（负无穷大，注意有个‘-’号）：  
  `double negative_infinity=-std::numeric_limits<double>::infinity();`
- 获得NaN的浮点值：  
  `long double not_a_number=std::numeric_limits<long double>::quiet_NaN()`

## 2.14 使用字符变量

1. **ascii字符**

```cpp
// 使用字符变量
#include <iostream>
#include <format>

int main()
{
    using std::cout;
    using std::endl;
    using std::format;

    char ch{'A'}; // 字面量字符
    cout << format("ch = {}\n", ch);
    /**************************************************************
    下面语句char letter{ch+2};会先把ch隐式转换成int,完成计算,
    再把int转换成char,所以编译器会有窄化转换的提醒（narrowing conversion）。
    采用其它方式则不会有窄化转换提醒了，如：
    1.char letter{ static_cast<char>(ch + 2) };
    2.char letter(ch + 2);
    3.char letter = ch + 2;
    **************************************************************/
    char letter{ch + 2};
    cout << "letter = " << letter << endl;
    ++ch;
    cout << format("ch = {}\n", ch);
    ch += 3;
    cout << format("ch is '{0}' which is code {0:#x}\n", ch);
    ch = 33; // 十进制字符
    cout << "ch = " << ch << endl;
    ch = '\x46'; // 十六进制字符
    cout << format("ch = {}\n", ch);
    ch = '\77'; // 八进制字符
    cout << "ch = " << ch << endl;

    return 0;
}
```

上面程序运行结果如下：  
<img src=<https://z.wiki/u/Nn3lyH>>

1. **unicode字符**  
宽字符字面量采用'L'开头

- `wchar_t z {L'Z'};`
- `wchar_t cc {L'\x00E7'}`
- 推荐使用以下几种类型:
    - char8_t  utf8[]  = u8"UTF-8文本";   // 明确UTF-8
    - char16_t utf16[] = u"UTF-16文本";   // 明确UTF-16
    - char32_t utf32[] = U"UTF-32文本";   // 明确UTF-32
- 标准库提供了标准输入流(wcin)和输出流(wcout)来读写wchar_t类型的字符,但没有提供处理char8_t、char16_t和char32_t字符数据的方式
- 在控制台中用cin()输入宽字符,可能是GBK编码,而不是UTF-8编码,会导致在控制台中输出乱码

| 前缀  |   类型   | 编码方案 | 字节/字符 | 引入标准 |
| :---: | :------: | :------: | :-------: | :------: |
|  无   |   char   | 窄字符集 |     1     |  C++98   |
|   L   | wchar_t  | 平台相关 |   2或4    |  C++98   |
|  u8   | char8_t  |  UTF-8   |    1-4    |  C++20   |
|   u   | char16_t |  UTF-16  |    2/4    |  C++11   |
|   U   | char32_t |  UTF-32  |     4     |  C++11   |

## 2.17 练习

1. 第1题

```cpp
// 第2章第1题
#include <iostream>
#include <format>

int main()
{

    using namespace std;

    unsigned inches{};
    unsigned feet{};
    unsigned inchesRemainder{};

    cout << "请输入整数值英寸数:";
    cin >> inches;
    feet = inches / 12;
    inchesRemainder = inches % 12;
    cout << format("{}英寸共有{}英尺{}英寸。\n", inches, feet, inchesRemainder);

    return 0;
}
```

2. 第2题

```cpp
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

3. 第3题

- 此题比较复杂,涉及三角函数知识,角度和弧度转换
- 数学模块应用
- 有些地方常量比变量更合理

```cpp
// 第3题
#include <iostream>
#include <cmath>
#include <numbers>

int main()
{
    using namespace std;

    const double inchesPerFoot{12.0};
    const double piDegrees{180.0};

    double feet{};
    double inches{};
    cout << "请分别输入你与树之间的距离是几英尺和几英寸(用空格隔开):";
    cin >> feet >> inches;
    const double distance{feet + inches / inchesPerFoot};

    double angle{}, angleToRadian{};
    cout << "请输入树顶的仰角（单位：度）:";
    cin >> angle;
    angleToRadian = angle * (numbers::pi / piDegrees); // 角度转换为弧度

    double eyeHeight{};
    cout << "请输入地面到眼睛的高度(英寸):";
    cin >> eyeHeight;
    eyeHeight /= inchesPerFoot;

    const double height{eyeHeight + distance * tan(angleToRadian)};                                   // 按公式计算树高度，这个三角函数要用弧度
    const unsigned heightFeet{static_cast<unsigned>(height)};                                         // 显式转换成无符号整数(英尺数)
    const unsigned heightInches{static_cast<unsigned>(round(inchesPerFoot * (height - heightFeet)))}; //(浮点数-整数)的余数乘12就是英寸数

    cout << "树的高度是" << heightFeet << "英尺"
         << heightInches << "英寸。" << endl;

    return 0;
}
```

4. 第4题

```cpp
// 第4题
#include <iostream>

int main()
{
    using namespace std;

    const double poundPerKg{2.2};
    const double footPerMeter{0.3048};
    const double inchesPerfoot{12};

    double weight{};
    cout << "请输入您的体重(磅):";
    cin >> weight;
    weight /= poundPerKg;

    double feet{};
    double inches{};
    double height{};
    cout << "请输入您的身高为几英尺几英寸(以空格分开输入):";
    cin >> feet >> inches;
    height = (feet + inches / inchesPerfoot) * footPerMeter;

    double BMI{};
    BMI = weight / (height * height);

    cout << "您的BMI指数为" << BMI << "。" << endl;

    return 0;
}
```

5. 第5题

```cpp
// 第5题
#include <iostream>
#include <format>

int main()
{
    using namespace std;

    const double poundPerKg{2.2};
    const double footPerMeter{0.3048};
    const double inchesPerfoot{12};

    double weight{};
    cout << "请输入您的体重(磅):";
    cin >> weight;
    weight /= poundPerKg;

    double feet{};
    double inches{};
    double height{};
    cout << "请输入您的身高为几英尺几英寸(以空格分开输入):";
    cin >> feet >> inches;
    height = (feet + inches / inchesPerfoot) * footPerMeter;

    double BMI{};
    BMI = weight / (height * height);

    cout << format("您的BMI指数是{:.1f}\n", BMI);

    return 0;
}
```

6. 第6题

```cpp
// 第6题
#include <iostream>
#include <format>
#include <numbers>

int main()
{
    using namespace std;

    const auto horLine{"------------------------------------------------------------"};

    cout << format("{:^60}\n", "表2-6 <numbers>模块中的数字常量示例");
    cout << format("{:^60}\n", horLine);
    cout << format("{:^19}|{:^19}|{:^20}\n", "常量", "描述", "近似值");
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.5f}...\n", "std:numbers::c", "自然对数的底", numbers::e);
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.5f}...\n", "std::numbers::pi", "π", numbers::pi);
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.5f}...\n", "std:numbers::sqrt2", "2的平方根", numbers::sqrt2);
    cout << format("{:^60}\n", horLine);
    cout << format("{:<19}|{:<19}|{:.3f}...\n", "std:numbers::phi", "黄金比例常量φ", numbers::phi);
    cout << format("{:^60}\n", horLine);

    return 0;
}
```

7. 第7题

```cpp
// 第7题
#include <iostream>
#include <format>
#include <numbers>
#include <cmath>

int main()
{
    using namespace std;

    // 以下定义常量必须使用constexpr关键字,不能用const,不然会报错.原因是format()要求格式字符串必须为编译时常量.
    constexpr auto WIDTH60{"{:^60}\n"};
    const auto HORIZON{"------------------------------------------------------------"};
    constexpr auto HEADER_ALIGN_CENTER{"{:^19}|{:^19}|{:^20}\n"};
    constexpr auto DECIMAL_PRECISION_5{"{:<19}|{:<19}|{:.5f}...\n"};
    constexpr auto DECIMAL_PRECISION_3{"{:<19}|{:<19}|{:.3f}...\n"};
    constexpr auto SCIENTIFIC_NOTATION{"{:<19}|{:<19}|{:.5E}...\n"};

    cout << format(WIDTH60, "表2-6 <numbers>模块中的数字常量示例");
    cout << format(WIDTH60, HORIZON);
    cout << format(HEADER_ALIGN_CENTER, "常量", "描述", "近似值");
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_5, "std:numbers::c", "自然对数的底", numbers::e);
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_5, "std::numbers::pi", "π", numbers::pi);
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_5, "std:numbers::sqrt2", "2的平方根", numbers::sqrt2);
    cout << format(WIDTH60, HORIZON);
    cout << format(DECIMAL_PRECISION_3, "std:numbers::phi", "黄金比例常量φ", numbers::phi);
    cout << format(WIDTH60, HORIZON);
    cout << format(SCIENTIFIC_NOTATION, "sin(π/4)", "科学记数法", sin(numbers::pi / 4));
    cout << format(WIDTH60, HORIZON);

    return 0;
}
```

上面练习第7题程序运行结果如下:  
<img src=<https://z.wiki/u/kINCSA>>