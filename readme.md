**目录**
- [前言](#前言)
- [第1章 基本概念](#第1章-基本概念)
  - [1.3 C++程序概念](#13-c程序概念)
    - [1.3.1 源文件](#131-源文件)
  - [1.9 表示数字](#19-表示数字)
    - [1.9.1 二进制数](#191-二进制数)
    - [1.9.2 十六进制数](#192-十六进制数)
    - [1.9.3 负的二进制数](#193-负的二进制数)
    - [1.9.4 八进制数](#194-八进制数)
    - [1.9.5 Big-Endian和Little-Endian系统](#195-big-endian和little-endian系统)
    - [1.9.6 浮点数](#196-浮点数)
  - [1.11 C++源字符](#111-c源字符)
  - [1.13 练习](#113-练习)
- [第2章 基本数据类型](#第2章-基本数据类型)
  - [2.1 变量、数据和数据类型](#21-变量数据和数据类型)
    - [2.1.1 定义整形变量](#211-定义整形变量)
    - [2.1.2 零初始化](#212-零初始化)
    - [2.1.3 定义有固定值的变量](#213-定义有固定值的变量)
  - [2.2 整形字面量](#22-整形字面量)
    - [2.2.1 十进制整形字面量](#221-十进制整形字面量)
    - [2.2.2 十六进制整形字面量](#222-十六进制整形字面量)
    - [2.2.3 八进制的整形字面量](#223-八进制的整形字面量)
    - [2.2.4 二进制的整形字面量](#224-二进制的整形字面量)
  - [2.3 整数的计算](#23-整数的计算)
  - [2.4 赋值运算](#24-赋值运算)
  - [2.5 sizeof运算符](#25-sizeof运算符)
  - [2.6 整数的递增和递减](#26-整数的递增和递减)
  - [2.7 定义浮点变量](#27-定义浮点变量)
  - [2.8 浮点字面量](#28-浮点字面量)
  - [2.9 浮点数的计算](#29-浮点数的计算)
    - [2.91 数学常量](#291-数学常量)
    - [2.9.2 数学函数](#292-数学函数)
    - [2.9.3 无效的浮点效果](#293-无效的浮点效果)
    - [2.9.4 缺点](#294-缺点)
  - [2.10 混合的表达式和类型转换](#210-混合的表达式和类型转换)
  - [2.11 显式类型转换](#211-显式类型转换)
  - [2.12 格式化字符串](#212-格式化字符串)
  - [2.13 确定数值的上下限](#213-确定数值的上下限)


# 前言
1. 个人学习C++的小屋,使用教材为《C++20入门实践(第6版)》。  
2. 操作系统为windows10_x64,编辑器为vscode1.101.2版,编译器为mingw15.1.0。  
⏰gogoup!  
# 第1章 基本概念  
![第1章导图](https://tc.z.wiki/autoupload/f/TCGPJbbsy8Ycjb3iVqtXI-dF-yTE5il903mGv8fj_W-yl5f0KlZfm6UsKj-HyTuv/20250725/kXm1/1073X883/Chapter1.png)
## 1.3 C++程序概念  
### 1.3.1 源文件  
```c++
// Ex1_01.cpp  

#include <iostream>  
//书中import <iostream>语句在mingw15.1.0中会报错,需改用旧方法包含头文件

int main()
{
    int answer{42};
    std::cout << "The answer to life, the universe, and everything is "
              << answer
              << std::endl;
    std::cin.get(); //解决调试时CMD窗口一闪而过的问题

    return 0;
}
```
> 🤞`知识点`  
不同方式变量初始化的差别  

| 特性         | int a = 10; (拷贝初始化) | int a{10}; (列表初始化)  |
| :----------- | :----------------------- | ------------------------ |
| 窄化转换     | 允许（可能有警告）       | 禁止（编译错误）         |
| 类初始化效率 | 可能低效（需隐式转换）   | 高效（直接调用构造函数） |
| 防止语法歧义 | 不能                     | 能                       |
| C++标准      | 所有版本                 | C++11起支持              |

## 1.9 表示数字  
### 1.9.1 二进制数  
324=3×10<sup>2</sup> + 2×10<sup>1</sup> + 4×10<sup>0</sup>  

二进制转换十进制的方法(其它进制转十进制也一样,只是进制基数不同,将2替换为其它进制的基数即可)  
1101=1×2<sup>3</sup> + 1×2<sup>2</sup> + 0×2<sup>1</sup> + 1×2<sup>0</sup>  

十进制转换二进制的方法口诀:除2取余，倒序排列。例子如下:  
| 步骤  | 十进制数 | 除以2 |  商   | 余数  |          备注          |
| :---: | :------: | :---: | :---: | :---: | :--------------------: |
|   1   |    13    | 13÷2  |   6   |   1   |       记录余数1        |
|   2   |    6     |  6÷2  |   3   |   0   |       记录余数0        |
|   3   |    3     |  3÷2  |   1   |   1   |       记录余数1        |
|   4   |    1     |  1÷2  |   0   |   1   | 记录余数1，商为0，停止 |

最终二进制数‌：倒序读余数（从步骤4到步骤1）：1（步骤4）、1（步骤3）、0（步骤2）、1（步骤1） → ‌1101‌。  

> 🤞`知识点`  
以任意n为基数表示的数,每个位数的数字是从0到n～1。十进制数为0～9,二进制数为0～1。  

> 🤞`知识点`  
十进制的基数为10,二进制的基数为2。设基数为n，如果有m位，就可以表示n<sup>m</sup>个整数,正值为0～n<sup>m</sup>-1。8位十进制数可以表示10<sup>8</sup>(100000000)个整数,正值为0～99999999；8位二进制数可以表示2<sup>8</sup>(256)个整数,正值为0～255。  

---
📖`拓展阅读`  

---
位（bit）、字节（byte）和字（word）是计算机数据存储与处理的核心单位，其层级关系和换算规则如下：
1. 基础定义与关系
    - ‌位（bit）‌  
计算机最小的数据单位，表示一个二进制位（0 或 1）。‌  
    - ‌字节（byte）‌  
‌1 字节 = 8 位‌，是存储容量的基本单位，可存储一个英文字符（如 ASCII 码）。  
    - 字（word）‌  
计算机一次处理的数据单元，由若干字节组成，长度由‌字长‌（CPU 位数）决定：
        - 16 位系统：1 字 = 2 字节 = 16 位
        - 32 位系统：1 字 = 4 字节 = 32 位
        - 64 位系统：1 字 = 8 字节 = 64 位
2. 关键概念总结  

| 单位  |   符号   |        组成关系         |            作用            |
| :---: | :------: | :---------------------: | :------------------------: |
|  位   | bit (b)  |     最小单位（0/1）     |       二进制数据基础       |
| 字节  | Byte (B) |     1 Byte = 8 bit      | 存储容量基准（如文件大小） |
|  字   | Word (W) | 1 Word = CPU位数/8 字节 |   CPU 单次处理数据的长度   |

3. 补充说明  
    - ‌字长‌：CPU 一次能处理的二进制位数，直接决定字的字节数（如 64 位 CPU 的字长为 64 位，即 8 字节）。  
    - ‌实际应用‌：
        - 位：硬件信号处理；
        - 字节：文件存储、内存地址分配；
        - 字：指令执行、数据总线传输。‌  
---

### 1.9.2 十六进制数  

表1-3  

| 十六进制 | 十进制 | 二进制 |
| :------: | :----: | :----: |
|    0     |   0    |  0000  |
|    1     |   1    |  0001  |
|    2     |   2    |  0010  |
|    3     |   3    |  0011  |
|    4     |   4    |  0100  |
|    5     |   5    |  0101  |
|    6     |   6    |  0110  |
|    7     |   7    |  0111  |
|    8     |   8    |  1000  |
|    9     |   9    |  1001  |
|    A     |   10   |  1010  |
|    B     |   11   |  1011  |
|    C     |   12   |  1100  |
|    D     |   13   |  1101  |
|    E     |   14   |  1110  |
|    F     |   15   |  1111  |

二进制转换十六进制口诀‌：四位一组，查表替换，高位补零。反过来十六进制转换二进制也是一样。  

| 1111  | 0101  | 1011  | 1001  | 1110  | 0001  |
| :---: | :---: | :---: | :---: | :---: | :---: |
|   F   |   5   |   B   |   9   |   E   |   1   |

十进制转换十六进制口诀:除16取余，倒序排列，10-15换字母  
| 步骤  | 十进制数 |   除以16    |   商    | 余数  |          备注          |
| :---: | :------: | :---------: | :-----: | :---: | :--------------------: |
|   1   | 16103905 | 16103905÷16 | 1006494 |   1   |       记录余数1        |
|   2   | 1006494  | 1006494÷16  |  62905  | 14(E) |       记录余数14       |
|   3   |  62905   |  62905÷16   |  3931   |   9   |       记录余数9        |
|   4   |   3931   |   3931÷16   |   245   | 11(B) |       记录余数11       |
|   5   |   245    |   245÷16    |   15    |   5   |       记录余数5        |
|   6   |    15    |    15÷16    |    0    | 15(F) | 记录余数15,商为0，停止 |

余数倒序,最终结果为F5B9E1。  

十六进制数转换十进制数公式:∑(每位十六进制值×16<sup>位置索引</sup>)。位置索引规则‌：从右向左，从0开始计数。  
F5B9E1 = 15×16<sup>5</sup> + 5×16<sup>4</sup> + 11×16<sup>3</sup> + 9×16<sup>2</sup> + 14×16<sup>1</sup> + 1×16<sup>0</sup>  
= 15728640 + 327680 + 45056 + 2304 + 224 + 1  
= 16103905  

> 🤞`知识点`  
现代计算机把整数存储在偶数字节的字中,一般是2、4、8或16字节,一个字节是8位,正好是两个十六进制数,所以内存中的任意二进制整数总是精确对应于若干个十六进制数。  

> 🤞`知识点`  
数制转换记忆规律:转十乘,十转除,十六转二4分组。  

### 1.9.3 负的二进制数
- 原码：绝对值二进制码  
- 反码：原码二进制数字，0变1，1变0  
- 补码：正数的补码等于原码，负数的补码等于反码+1  

> 👉`重点`  
补码的核心是‌用加法代替减法‌，同时解决负数表示问题。做加减法计算时‌所有数用补码相加，舍弃溢出位，即得结果。  

### 1.9.4 八进制数
> 👉`重点`  
八进制值有一个前导0！076是八进制,而76是十进制,一定要注意分清。  

### 1.9.5 Big-Endian和Little-Endian系统

- Big-Endian(大端序),最高位字节在低字节地址  
    - 网络协议 (TCP/IP 标准规定使用大端序，称为“网络字节序”)。
    - 某些处理器架构：如 Motorola 68000, IBM POWER (包括某些 PowerPC), Sun SPARC (历史主流), Java虚拟机内部表示等。

| 地址  | 0x1000 | 0x1001 | 0x1002 | 0x1003 |
| :---: | :----: | :----: | :----: | :----: |
| 内容  |  0x12  |  0x34  |  0x56  |  0x78  |
- Little-endian (小端序),最低位字节在低字节地址  
    - ‌x86 和 x86-64 架构 (Intel, AMD 处理器)‌。
    - ARM 处理器 (通常可配置，但移动设备、嵌入式系统常用小端)。
    - DEC VAX, 6502 等。

| 地址  | 0x1000 | 0x1001 | 0x1002 | 0x1003 |
| :---: | :----: | :----: | :----: | :----: |
| 内容  |  0x78  |  0x56  |  0x34  |  0x12  |

`理解重要性`
- 数据交换：‌ 当数据在不同架构（大端和小端）的计算机之间传输（通过网络、文件等）时，如果不进行字节序转换，接收方读取到的数值将是错误的！这也是为什么网络协议强制使用大端序（网络字节序），发送方和接收方在进行网络通信前都需要调用函数 (htonl, htons, ntohl, ntohs) 在主机字节序和网络字节序之间进行转换。
- ‌文件格式：‌ 文件格式需要明确定义其数据的字节序，以确保在不同系统上都能正确读取。常见格式如 PNG、JPEG 通常使用大端序。
- ‌调试：‌ 调试器查看内存内容时，理解字节序对于正确解读数值至关重要。
- ‌低级编程：‌ 直接操作内存或进行二进制数据处理时，必须考虑字节序。

> 🀄`结论`  
理解这两种字节序对于计算机体系结构、网络编程、文件格式解析和底层系统编程至关重要。现代计算机系统中，x86/x64 的绝对主导地位使得小端序在日常开发中更为常见，但在网络传输和跨平台数据交换时，大端序（网络字节序）是必须遵循的标准。  

### 1.9.6 浮点数
- 浮点数一般只是精确数字的近似表示。
- 不同量级的数字执行相加或相减操作要小心,有可能不产生效果。
- 两个几乎相等的数相减,结果可能只有一两位小数精度。

## 1.11 C++源字符
```c++
// Ex1_02.cpp
// Using escape sequences
#include <iostream>
int main(){
    std::cout <<"\"Least \'said\' \\\n\t\tsonnest \'mended\'.\"" << std::endl;
    std::cin.get();
    return 0;
}
```
## 1.13 练习
1. 创建\编译\链接\执行一个程序,在屏幕上输出文本"Hello World"。
```c++
#include <iostream>
int main()
{
    std::cout << "Hello World" << std::endl;
    std::cin.get();
    return 0;
}
```
2. 创建并执行一个程序,在一行上输出自己的姓名,在下一行上输出年龄。
```c++
#include <iostream>
int main()
{
    std::cout << "李白\n18岁" << std::endl;
    std::cin.get();
    return 0;
}
```
3. 下面的程序有几处编译错误。请指出这些错误并更正,使程序能正确编译并运行。
```c++
#import <iostream> //少分号
Int main //I要小写,同时函数名少括号
{
    std:cout << "Hola Mundo!" << std:endl //两个std:都少一个":",而且语句结尾少";"
}
```
```c++
#include <iostream> //因编译器不支持#import,改为#include
int main()
{
    std::cout << "Hola Mundo!" << std::endl;
    std::cin.get();
    return 0;
}
```
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
    std::cin.get();
    return 0;
}
```
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

字面量可以有后缀,如-123L、98U、12345ULL等，大小写不限，U和L前后不限。一般情况下实际编程不写后缀，但在某些情况下，需要添加正确的字面量后缀，例如初始化一个auto类型的变量或者调用有字面量实参的重载函数（第8章介绍）时。  
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
    std::cout << "22'333uLL + 0xFF00FF00u + 0765321L + 0b110010101101U = " << finalResult << std::endl;
    std::cin.get();
    return 0;
}
```

> 🤞`知识点`  在整形字面量中可以使用单引号作为分隔符,使字面量更容易阅读。包括十进制、十六进制和二进制的字面量，例如123'456'789、0xFF00'00FFu、0b11001010'11011001。

 ## 2.3 整数的计算
 - 二元运算符:有两个操作数,如`+、-、*、/、%`等。
 - 一元运算符:只有一个操作数,如`-`(取反运算)。
 - 取模运算符%是对除法运算符/的补充：（x/y）*y +（x%y）= x。

> 👉`重点`  c++中整数除法结果总是整数,结果不会出现小数!

"/"或"%"的右操作数为0,后果很严重!除数为变量时,须编程人员主动防御(先判断被除数是否为0)。
|         场景         |       整数除法       |       浮点数除法        |
| :------------------: | :------------------: | :---------------------: |
|     除数为常量0      |      编译报错 ❌      |       编译报错 ❌        |
| ‌除数为变量（值为0）‌ | 编译通过 ✅运行崩溃 💥 | 编译通过 ✅返回 inf/nan ️ |

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
    total_inches = yards * feet_per_yard * inches_per_foot + feet * inches_per_foot + inches;
    cout << "这个距离相当于" << total_inches << "英寸。" << endl;

    cout << "请输入一个距离(英寸):";
    cin >> total_inches;
    inches = total_inches % inches_per_foot;
    feet = total_inches / inches_per_foot;
    yards = feet / feet_per_yard;
    feet = feet % feet_per_yard;
    cout << "这个距离相当于" << yards << "码" << feet << "英尺" << inches << "英寸。\n";

    cin.get();
    return 0;
}
```
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
    std::cout << "表达式\"height*height/2\"结果占用" << sizeof(height * height / 2) << "字节。" << std::endl;
    std::cin.get();

    return 0;
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

|  数据类型   |        说明        | 精度(十进制位数) |                     取值范围                      |
| :---------: | :----------------: | :--------------: | :-----------------------------------------------: |
|    float    |    单精度浮点数    |        7         |   ±1.18×10<sup>-38</sup>～±3.4×10<sup>38</sup>    |
|   double    |    双精度浮点数    |    15(几乎16)    |  ±2.22×10<sup>-308</sup>～±1.8×10<sup>308</sup>   |
| long double | 扩展的双精度浮点数 |      18或19      | ±3.65×10<sup>-4932</sup>～±11.8×10<sup>4932</sup> |
> 👉`重点`  浮点数的精度是包含整数位和小数位的全部数字的（不包含小数点），所以要谨慎选择浮点数的数据类型。要注意理解精度和取值范围的含义。“大多数情况下，使用double类型就够了。通常，只有当速度或数据大小非常关键时，才会使用float。”  

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
    - 所以，float 能保证大约 7位十进制有效数字 是精确的。当你存储一个像 123456789.0f 的float时，它可能只能精确表示为 123456790.0 或 123456788.0（后几位不精确），因为有效数字超过了7位。但它能精确表示像 1.234567 或 12345.67 这样的数（只要总的有效数字不超过约7位）。  
2. 巨大范围（约 ±3.4e38）的来源：  
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
`程序运行结果为：1.5/0=inf；  inf+1.5=inf；  0/0=nan `

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

5. `[[fill]align][sign][#][0][width][.precision][type]`,可选的格式化选项
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

<img src=https://z.wiki/u/J78qrS>

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
<img src=https://z.wiki/u/9HwRnn>

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
使用`numeric_limits<data type>::min()`、`numeric_limits<data type>::lowest()`和`numeric_limits<data type>::max()`读取基本数据类型的上下限。
```cpp
// Ex2_07.cpp
//  Finding maximum and minimum values for data types
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


