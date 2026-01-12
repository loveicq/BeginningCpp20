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
```c++
#include <iostream>
#include <cctype>

int main()
{
    char reply{};
    int count{};
    double temperature{};
    double total{};

    do
    {
        std::cout << "Enter a temperature reading: ";
        std::cin >> temperature;

        total += temperature;
        ++count;

        std::cout << "Do you want to enter another?(y/n): ";
        std::cin >> reply;

    } while (std::tolower(reply) == 'y');

    std::cout << "The average temperature is " << total / count << std::endl;
}
```
📌do-while语句有分号,但普通while循环的while()后面不应该加上分号.
## 5.12 嵌套的循环
```C++
#include <iostream>
#include <format>
#include <cctype>

int main()
{
    size_t table{};
    const size_t table_min{2};
    const size_t table_max{12};
    char reply{};

    do
    {
        std::cout << std::format("What size table would you like ({} to {})? ", table_min, table_max);
        std::cin >> table;
        std::cout << std::endl;

        if (table < table_min || table > table_max)
        {
            std::cout << "Invalid table size entered.Program terminated." << std::endl;
            return 1;
        }

        // 打印列表头
        std::cout << std::format("{:>6}", '|'); // 打印表头第一个竖线
        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i); // 打印表头后面的数字和竖线
        }
        std::cout << std::endl;

        // 打印表头下面的分隔线
        for (size_t i{}; i <= table + 1; ++i)
        {
            std::cout << "------";
        }
        std::cout << std::endl;

        // 外循环打印行内容
        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i); // 打印行表头

            // 内循环打印列内容
            for (size_t j{1}; j <= table; ++j)
            {
                std::cout << std::format(" {:3} |", i * j);
            }
            std::cout << std::endl; // 打印完最后一列换到下一行
        }

        std::cout << "\nDo you want another table(y or n)? ";
        std::cin >> reply;
    } while (std::tolower(reply) == 'y');
}
```
此例可学习的点:  
1. 采用format()可以结果和定位字符一起输出,如`format(" {:3} |",i*j)`输出"空格+占三位的数字+空格+|",便于对齐.
2. 先输出表头,再用多重循环输出行和列的内容:  
    - 第1重循环输出多少行,变量 i 控制行数
    - 第2重循环输出多少列,变量 j 控制列数
3. 最外面再套一个大循环do-while,用于处理是否再开始一轮
4. 变量table用于控制要打印的行数和列数及其乘法结果,table_min和table_max控制最小和最大行列数,防止输入不合理的数值.
## 5.13 跳过循环迭代
```c++
#include <iostream>
#include <format>
#include <cctype>

int main()
{
    constexpr auto header_format = "{:^11}{:^11}{:^11}{:^11}\n";
    constexpr auto body_format = "{0:^11}{0:^11X}{0:^11d}{0:^11b}\n";

    std::cout << std::format(header_format, "Character", "Hexadecimal", "Decimal", "Binary");
    char ch{};
    do
    {
        if (!std::isprint(ch))
        {
            continue;
        }
        std::cout << std::format(body_format, ch);
    } while (ch++ < 127);
}
```
修改成for循环
```c++
#include <iostream>
#include <format>
#include <cctype>

int main()
{
    constexpr auto header_format = "{:^11}{:^11}{:^11}{:^11}\n";
    constexpr auto body_format = "{0:^11}{1:^11d}{1:^11X}{1:^11b}\n";

    std::cout << std::format(header_format, "Character", "Decimal", "Hexadecimal", "Binary");

    for (int ch{}; ch <= 127; ++ch)
    {
        if (!std::isprint(static_cast<char>(ch)))
        {
            continue;
        }
        std::cout << std::format(body_format, static_cast<char>(ch), ch);
    }
}
```
## 5.14 循环的中断
**无限循环**
- for(;;)
- while(true)
- do-while无限循环比较少见
```c++
#include <iostream>
#include <format>
#include <cctype>

int main()
{
    const size_t table_min{2};
    const size_t table_max{12};
    const size_t max_tries{3};
    size_t table{};
    char reply{};

    do
    {
        for (size_t count{1};; ++count)
        {
            std::cout << std::format("What size table would you like ({} to {})?", table_min, table_max);
            std::cin >> table;
            if (table >= table_min && table <= table_max)
            {
                break;
            }
            else if (count < max_tries)
            {
                std::cout << "Invalid input - try again.\n";
            }
            else
            {
                std::cout << "Invalid table size entered - yet again!\nSorry,only "
                          << max_tries << " allowed - program terminated." << std::endl;
                return 1;
            }
        }

        std::cout << std::format("{:>6}", '|');
        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format(" {:3} |", i);
        }
        std::cout << std::endl;

        for (size_t i{}; i <= table + 1; ++i)
        {
            std::cout << "------";
        }
        std::cout << std::endl;

        for (size_t i{1}; i <= table; ++i)
        {
            std::cout << std::format("{:4} |", i);
            for (size_t j{1}; j <= table; ++j)
            {
                std::cout << std::format("{:4} |", i * j);
            }
            std::cout << std::endl;
        }

        std::cout << "Do you want another table (y or n)?";
        std::cin >> reply;
    } while (std::tolower(reply) == 'y');
}
```
```c++
#include <iostream>
#include <format>

int main()
{
    const size_t size{1000};
    double x[size]{};
    size_t count{};

    while (true)
    {
        double input{};
        std::cout << "Enter a non-zero value, or 0 to end: ";
        std::cin >> input;
        if (input == 0)
        {
            break;
        }
        x[count] = input;

        if (++count == size)
        {
            std::cout << "Sorry, I can only store " << size << "values.\n";
            break;
        }
    }
    if (count == 0)
    {
        std::cout << "Nothing to sort..." << std::endl;
        return 0;
    }

    std::cout << "Staring sort..." << std::endl;

    while (true)
    {
        bool swapped{false};

        for (size_t i{}; i < count - 1; ++i)
        {
            if (x[i] > x[i + 1])
            {
                const auto temp = x[i];
                x[i] = x[i + 1];
                x[i + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }

    std::cout << "Your data in ascending sequence:\n";
    const size_t perline{10};
    size_t n{};
    for (size_t i{}; i < count; ++i)
    {
        std::cout << std::format("{:8.1f}", x[i]);
        if (++n == perline)
        {
            std::cout << std::endl;
            n = 0;
        }
    }
    std::cout << std::endl;
}
```
## 5.15 使用无符号整数控制for循环
从无符号整数减去值时应当小心.任何在数学意义上为负的值将被转换为一个极大的正数.这类错误在循环控制表达式中会造成灾难性后果.如果0-1的结果是numeric_limits<size_t>::max().
解决方法:
- 进入循环之前检查值是否为0,如案例Ex5_09.
- 强制转换为带符号整数.`for (int i{};i<staic_cast<int>(count)-1;++i)`
- 重写循环使其不再使用减法.`for(size_t i{};i+1<count;++i)`
```c++
    // 倒序输出案例Ex5_09的数组
    n = 0;
    for (auto i{static_cast<int>(count - 1)}; i >= 0; --i)
    {
        std::cout << std::format("{:8.1f}", x[i]);
        if (++n == perline)
        {
            std::cout << std::endl;
            n = 0;
        }
    }
    std::cout << std::endl;
```
## 5.16 字符数组
char 类型的数组:
1. 字符数组,每个元素存储一个字符。`char vowels[5]{'a','e','i','o','u'}`没有以'\0'结尾，所以是字符数组。
2. 字符串,结尾用空字符'\0'终止(C样式的字符串)。`char vowels[6]{'a','e','i','o','u'}`数组定义了6个元素，只初始化5个，第6个就默认为0,即'\0'，所以是字符串。字符串也可以看作字符数组。
3. 另外的数组定义
    - `char vowels[]{'a','e','i','o','u'};`--字符数组，编译器设置数组大小
    - `char name[10]{"Mae West"}';`--字符串，初始化为一个字符串字面量,10个元素
    - `char name[]{"Mae West"};`，字符串,9个元素
4. 使用数组名可以输出字符串。`std::cout<<name<<std::endl;`。如果char数组没有用空字符'\0'结束，直接输出数组名，程序很可能崩溃。
5. cin流的getline()函数可以读取一系列字符，包括空格。默认情况下，在读取换行符'\n'后输入结束。
6. getline()有两个必选参数和一个可选参数。`std::cin.getline(test,max_length,'*')`，第一个参数指定存储的位置，第二个参数指定要存储的最大字符数，第三个指定'\n'的替代字符（输入多行文本时可用这个参数）。
7. 空字符'\0'会被转换为布尔值false，所以有以下判断形式`for (int i{};text[i];i++)`。text[i]等价于text[i] == '\0'。

```c++
#include <iostream>
#include <cctype>

int main()
{
    const unsigned max_length{100};
    char text[max_length]{};

    std::cout << "Enter a line of text:" << std::endl;
    std::cin.getline(text, max_length);
    std::cout << "You entered:\n"
              << text << std::endl;

    size_t vowels{};
    size_t consonants{};
    for (int i{}; text[i] != '\0'; i++)
    {
        if (std::isalpha(text[i]))
        {
            switch (std::tolower(text[i]))
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                ++vowels;
                break;
            default:
                ++consonants;
            }
        }
    }
    std::cout << "Your input contained " << vowels << " vowels and "
              << consonants << " consonants." << std::endl;
}
```
## 5.17 多维数组
- 一维数组:一个索引值来引用元素
- 二维数组:两个索引值来引用元素
- 三维数组:三个索引值来引用元素
- `double carrots[3][4] {};`,第一个索引值指定行,第二个索引值指定列
- 数组的元素存储在一个连续的内存块中
- `std::cout<<carrots<<std::endl;`和char类型的数组不同,因为类型是double,这条语句会输出一个十六进制值,它是数组中第一个元素的内存地址
- `std::size(arr)`返回数组第一维的大小,一维数组返回元素个数,二维数组返回第一维的数量(即行数)
### 5.17.1 初始化多维数组
1. 第一种形式(元素不齐)
```c++
    double carrots[3][4]
    {
        {2.5,3.2,3.7,4.1},
        {4.1,3.9,1.6,3.5},
        {2.8,2.3,0.9,1.1}
    };
```
2. 第二种形式(元素不齐)
```c++
    double carrots[3][4]
    {
        {2.5,3.2},      //后两个元素初始化为0.0
        {4.1},          //后三个元素初始化为0.0
        {2.8,2.3,0.9}   //后一个元素初始化为0.0
    };
```
3. 第三种形式(元素不齐)
```c++
    double carrots[3][4]{1.1,1.2,1.3,1.4,1.5,1.6,1.7};//元素填满一行再一行,不够则初始化为0.0
```
**在默认情况下设置维数**  
可以让编译器根据初始值,决定数组的第一个维度的大小.
1. 二维数组
```c++
    double carrots[][4]
    {
        {2.5,3.2},
        {4.1},
        {2.8,2.3,0.9}
    };
```
2. 三维数组
```c++
    double numbers[][3][4]
    {
        {
            {2,4,6,8},
            {3,5,7,9},
            {5,8,11,14}
        },
        {
            {12,14,16,18},
            {13,15,17,19},
            {15,18,21,24}
        }
    };
```
### 5.17.2 多维字符数组
1. 在用字符串字面量初始化char类型的二维数组时,不需要对每行字面量加上大括号——界定字面量的双引号就完成了大括号的工作。
```c++
//Ex5_11.cpp
#include <iostream>
#include <array>

int main()
{
    const size_t max_length{80};
    char stars[][max_length]{
        "Fatty Arbuckle",
        "Clara Bow",
        "Boris Karloff",
        "Mae West",
        "Lassie",
        "Slim Pickens",
        "Oliver Hardy",
        "Greta Garbo"};

    size_t choice{};
    std::cout << "Pick a lucky star! Enter a number between 1 and  "
              << std::size(stars) << ": ";
    std::cin >> choice;

    if (choice >= 1 && choice <= std::size(stars))
    {
        std::cout << "Your lucky star is " << stars[choice - 1] << std::endl;
    }
    else
    {
        std::cout << "Sorry, you haven't got a lucky star." << std::endl;
    }
}
```
2. 多维字符数组只需要一个索引值就可以输出一个字符串
3. 索引被指定为choice-1，因为choice值从1开始，而索引值需要从0开始。
## 5.18 在运行期间给数组分配内存空间
**注意**：这个案例在gcc15.1.0中提示错误：“ISO C++ forbids variable length array 'height' [-Wvla]”【C++标准禁止使用变长数组（VLA）】
1. 案例一
```c++
// Ex5_12.cpp
#include <iostream>
#include <format>

int main()
{
    size_t count{};
    std::cout << "How man height will you enter? ";
    std::cin >> count;
    int height[count];

    size_t entered{};
    while (entered < count)
    {
        std::cout << "Enter a height (in inches): ";
        std::cin >> height[entered];
        if (height[entered] > 0)
        {
            ++entered;
        }
        else
        {
            std::cout << "A height must be positive - try again.\n";
        }

        unsigned total{};
        for (size_t i{}; i < count; ++i)
        {
            total += height[i];
        }

        std::cout << std::format("The average height is {:.1f}\n",
                                 static_cast<double>(total) / count);
    }
}
```
2. 案例二
```c++
// Ex5_12A.cpp
#include <iostream>
#include <format>

int main()
{
    size_t count{};
    std::cout << "How man height will you enter? ";
    std::cin >> count;
    int height[count];

    size_t entered{};
    unsigned total{};
    while (entered < count)
    {
        std::cout << "Enter a height (in inches): ";
        std::cin >> height[entered];
        if (height[entered] > 0)
        {
            total += height[entered++]; // 注意必须是后缀++
        }
        else
        {
            std::cout << "A height must be positive - try again.\n";
        }

        std::cout << std::format("The average height is {:.1f}\n",
                                 static_cast<double>(total) / count);
    }
}
```
## 5.19 数组的替代品
类模板
- `std::array<T,N>`
- `std::vector<T>`
### 5.19.1 使用`array<T,N>`容器
1. T表示Type,元素类型;N表示Number,编译时常量整数值。
2. `array<T,N>`模板在`<array>`模块中定义。
3. `std::array<double,100> values;`创建一个名称为values的对象,这个对象包含100个double类型的元素,其中`std::array<double,100>`是values对象的数据类型。
4. 大部分标准库类型，包括vector<>和其它所有容器，总是初始化其元素，通常初始化为0。但是array<>是特殊情况，如果不指定初始值，则元素是垃圾值。也可以在定义时初始化其元素：`std::array<double,100>values{0.5,1.0,1.5,2.0};`，初始化前4个元素，后面的元素是0。
5. C++17开始，编译器可以通过给定的初始化列表来推断模板参数。`std::array values {0.5,1.0,1.5,2.0}`，其类型是`std::array<double,4>`，并且这里推断出数组的大小为4，不是前面所说的100。要对模板参数进行推断，初始化列表就不能为空，且其中值的类型必须相同。
6. array<>对象的fill()函数也可以把所有元素设置为某个给定的值。`values.fill(std::numbers::pi);`。
7. array<>对象的size()函数返回size_t类型的元素个数。  

<h4 style="color:#8B4513;font-weight:bold;font-style:italic;">1. 访问各个元素</h4>  

- 使用索引可以访问和使用元素，其方式和标准数组相同。`values[3]=values[2]+2.0*values[1];`
```c++
//求所有元素的总和
double total{};
for(size_t i{};i<values.size();++i)
{
    total+= values[i];
}
```
- array<>对象是一个范围，可以使用基于范围的for循环
```c++
//基于范围的for循环求所有元素的总和
double total{};
for(auto value:values)
{
    total+=value;
}
```
- array<>对象的at()函数会检查索引值是否超出合法的范围，这个函数的参数是一个索引。如果运行时索引值i超出合法范围，at(i)函数会抛出一个异常。而values[i]则不会，很可能导致未定义行为。
```c++
double total{};
for(size_t i{};i<values.size();++i)
{
    total+=values.at(i);
}
```
- array<>对象的values.front()函数等同于values[0],values.back()函数等同于values[values.size()-1]。  

<h4 style="color:#8B4513;font-weight:bold;font-style:italic;">2.将array<>作为整体操作</h4>  


