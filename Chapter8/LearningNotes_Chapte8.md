# 第8章 定义函数

函数是C++程序中的基本组成块  

## 8.1 程序的分解

**调用栈**记录了所有函数调用的信息，以及传递给每个函数的数据的详细信息。  

### 8.1.1 类中的函数

每个类定义通常包含表示操作的函数（类函数）。如std::String类对象的length()函数和find()函数；`std::istream`类的`std::cin`对象和`std::ostream`类的`std::cout`对象（这两个类均在`<iostream>`头文件中定义）等。  

### 8.1.2 函数的特征

函数应执行单个已定义好的操作，而且相对较短，大多数函数不涉及太多代码。  

## 8.2 定义函数

1. 函数定义：函数由函数头和函数体组成  

    - 函数头
        1. 返回类型：基本类型、类类型、指针类型和引用类型
        2. 函数名：与变量相同的命名规则
        3. 参数列表：放在函数名后的小括号中，用逗号分隔的列表。函数可以没有参数  
        函数名和参数列表的组合称为函数的**签名**。
    - 函数体：位于大括号内的代码块
2. 形参和实参：形参是函数原型的参数，实参是调用函数的参数，两者的数据类型应该一致，如果不一致可能会进行隐式转换，如果不能转换，编译会失败
3. 函数或参数命名应该有具体作用描述，对代码可读性有很大好处
4. 返回类型为void的函数没有返回值，不能在表达式中使用

### 8.2.1 函数体

```cpp
// Ex8_01.cpp
// 计算幂函数
#include <iostream>
#include <format>

double power(double x, int n)
{
    double result{1};

    if (n >= 0)
    {
        for (int i{1}; i <= n; ++i)
            result *= x;
    }
    else
    {
        for (int i{1}; i <= -n; ++i)
            result /= x;
    }

    return result;
}

int main()
{
    for (int i{-3}; i <= 3; ++i)
        std::cout << std::format("{:10g}", power(8.0, i));

    std::cout << std::endl;
}
```

上面示例执行结果如下：

---

```cpp
0.00195312  0.015625     0.125         1         8        64       512  
```

---

这个示例程序其实在标准库已经提供，而且更好用。在`<cmath>`模块中提供。

### 8.2.2 返回值

1. 返回类型不是void的函数必须返回一个值，类型在函数头中指定
2. main()函数的右大括号相当于返回0
3. return语句结束函数，继续从调用点向下执行
4. 函数体中可以有多个return语句，每个return语句可以返回不同的值
5. 函数只能返回一个值，但是这个值可以是任何内容，比如数组、容器、容器的容器等，所以其实可以返回无数的值

**return语句的工作方式**  

1. 系统会自动复制函数返回值的一个副本，该副本对调用函数是可用的。所以函数结束返回值（局部变量）销毁，不影响结果，因为已经有副本
2. return语句的一般形式：`return expression`，其中expression必须为函数头中返回指定值的类型，或者可以转换为该类型。它可以是任何类型，甚至可以是返回函数的调用，或者是返回调用自身（递归）
3. 返回值为void类型的函数，return后面不能有expression，只能写成`return;`，或者不写`return;`，程序执行到右大括号就相当于执行`return;`了

### 8.2.3 函数声明

```cpp
// Ex8_02.cpp
// 计算幂，重新构建。编译此程序会报错，因为函数声明在调用之后
#include <iostream>
#include <format>

int main()
{
    for (int i{-3}; i <= 3; ++i)
    {
        std::cout << std::format("{:10g}", power(8.0, i));
    }

    std::cout << std::endl;
}

double power(double x, int n)
{
    double result{1};

    if (n == 0)
        return 1;
    if (n > 0)
    {
        for (int i{1}; i <= n; ++i)
            result *= x;
    }
    else
    {
        for (int i{1}; i <= -n; ++i)
            result /= x;
    }

    return result;
}
```

上面示例程序编译错误，提示如下：

---

```cpp
'power' was not declared in this scope; did you mean 'tolower'?
```

---

需要使用函数声明的场景：

- 多个源文件，一个源文件中的函数要调用另一个源文件的函数
- 递归函数

**函数原型**  

1. 函数原型定义了函数名、函数的返回类型及其参数列表。函数原型有时称为函数声明
2. 函数声明要放在调用之前，函数定义（即函数实现）也是声明
3. 函数原型与函数头相同，最后要加上分号。函数原型中的参数名可以与函数头不同，但参数的类型必须相同。甚至可以省略参数名，只保留参数类型，但最好总是包含有描述性的参数名
4. 要习惯为源文件定义的每个函数编写函数原型，避免编译错误和方便其他程序员了解代码的功能

## 8.3 给函数传递实参

通常使用两种机制向函数传递实参：**按值传递**和**按引用传递**

### 8.3.1 按值传递

- 在按值传递机制中，指定为实参的变量值或常量值不会传递给函数，而是创建实参的副本，把这些副本传递的函数
- 编译器会把实参的副本存储在调用栈的一个临时位置，在函数执行过程中对函数参数的所有引用都被映射到实参的临时副本上。执行完函数后，就废弃实参的副本
- 按值传递不会改变调用函数拥有的变量值，但如果要改变，可以使用传递指针的方法

```cpp
// Ex8_03.cpp
// 未能修改函数参数的原始值
#include <iostream>
double changeIt(double value_to_be_changed);

int main()
{
    double it{5.0};
    double result{changeIt(it)};

    std::cout << "After function execution,it = " << it
              << "\nResult returned is " << result << std::endl;
}

double changeIt(double it)
{
    it += 10.0;
    std::cout << "Within function,it = " << it << std::endl;
    return it;
}
```

上面示例程序运行结果如下：

---

```cpp
Within function,it = 15  
After function execution,it = 5  
Result returned is 15
```

---

**1.给函数传递指针**  

函数参数是指针类型时，按值传递机制会像以前那样运行。但是，指针包含另一个变量的地址，指针的副本包含同一个地址，因此指向相同的变量。

```cpp
// Ex8_04.cpp
// 修改调用者变量的值
#include <iostream>

double changeIt(double *pointer_to_it);
int main()
{
    double it{5.0};
    double result{changeIt(&it)};

    std::cout << "After function execution,it = " << it
              << "\nResult returned is " << result << std::endl;
}

double changeIt(double *pit)
{
    *pit += 10.0;
    std::cout << "Within function,*pit = " << *pit << std::endl;
    return *pit;
}
```

上面示例程序运行结果如下：

---

```cpp
Within function,*pit = 15
After function execution,it = 15
Result returned is 15
```

---

**2.给函数传递数组**  

数组名本质是地址，传递给函数会复制数组的地址  

- 传递数组的地址比传递数组更高效。数组不能作为一个实参按值传递每个元素，因为每个参数都表示一个单独的数据项
- 函数不处理原始数组变量，但通过副本，函数体中的代码可以把表示数组的参数作为指针来看待，包括修改它包含的地址，可以使用指针表示法的强大功能

```cpp
// Ex8_05.cpp
// 将数组传递给函数
#include <iostream>
#include <array> //用于 std::size()

double average(double array[], size_t count); // 函数原型

int main()
{
    double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average(values, std::size(values)) << std::endl;
}

// 计算平均值的函数
double average(double array[], size_t count)
{
    double sum{}; // 在此累加总和
    for (size_t i{}; i < count; ++i)
        sum += array[i]; // 对数组元素求和
    return sum / count;  // 返回平均值
}
```

上面示例程序运行结果如下：

---

```cpp
Average = 5.5 
```

---

❗注意：不能通过在average()函数中使用sizeof运算符或std::size()函数来避免指定count参数。数组参数只是存储数组的地址，而不是数组本身。  

也可以把传递给函数的数组看成指针，使用指针表示法访问元素，如以下函数。甚至都不用修改函数声明。

```cpp
double average(double* array, size_t count)
{
    double sum{}; // 在此累加总和
    for (size_t i{}; i < count; ++i)
        sum += *array++; // 对数组元素求和
        /*
        sum += *array++;等价于以下语句:
        sum += *array;
        array++;
        */
    return sum / count;  // 返回平均值
}
```

❗注意：当按值传递数组时，绝不应该指定维数。按值传递的数组总是作为指针传递，编译器不会检查其维数。`double average10(double array[10])`完全等效于`double average10(double array[])`和`double average10(double* array)`两种形式

**3.const指针参数**  

average()函数只需要访问数组元素的值，不需要修改它们。这需要把数组参数类型指定为const。而count不用const，因为按值传递是复制实参，不能修改实参的值，但count参数最好还是加上const。

```cpp
//要注意，函数声明也要相应修改，加上const
double average(const double* array,const size_t cont)
{
    double sum{};
    for(size_t i{};i<count;++i)
        sum += *array++;
    return sum / count;
}
```

**4.把多维数组传递给函数**  

```cpp
// Ex8_06.cpp
// 将二维数组传递给函数
#include <iostream>
#include <array> //用于 std::size()

double yield(const double values[][4], size_t n);

int main()
{
    double beans[3][4]{{1.0, 2.0, 3.0, 4.0},
                       {5.0, 6.0, 7.0, 8.0},
                       {9.0, 10.0, 11.0, 12.0}};
    std::cout << "Yield= " << yield(beans, std::size(beans)) // std::size(beans)实际得出数组的行数（第一维数量）
              << std::endl;
}

// 计算总产量的函数
double yield(const double array[][4], size_t size)
{
    double sum{};
    for (size_t i{}; i < size; ++i) // 遍历行
        for (double val : array[i]) // 遍历行中的各元素
            sum += val;
    return sum;
}
```

上面示例程序运行结果如下:

---

```cpp
Yield= 78 
```

---

- 多维数组并不适合使用指针表示法，如`sum += *(*(array+i)+j)`。用数组表示法会清楚得多。
- 第二维可以用基于范围的for循环，因为编译器知道array[i]的大小，但不知道第一维的大小，所以外层循环不能用范围for循环。

### 8.3.2按引用传递

引用只是另一个变量的别名，使用引用参数不会进行复制。  

**1.对比引用与指针**  

```cpp
// Ex8_07.cpp
// 修改调用者变量的值 - 引用与指针
#include <iostream>

void change_it_by_pointer(double *reference_to_it);   // 传递指针（按值传递）
void change_it_by_reference(double &reference_to_it); // 按引用传递

int main()
{
    double it{5.0};

    change_it_by_pointer(&it); // 现在我们传递地址
    std::cout << "After first function execution,it = " << it << std::endl;

    change_it_by_reference(it); // 现在我们传递引用，而不是值！
    std::cout << "After second function execution,it = " << it << std::endl;
}

void change_it_by_pointer(double *pit)
{
    *pit += 10.0; // 这会修改原始的double值
}
void change_it_by_reference(double &pit)
{
    pit += 10.0; // 这也会修改原始的double值！
}
```

上面示例程序的运行结果如下：

---

```cpp
After first function execution,it = 15
After second function execution,it = 25
```

---

- 如想允许nullptr实参，就不能使用引用
- 如果从上下文不能明显看出函数会修改实参，就绝不应该修改实参的值
- 通过指向const值的引用来传递实参，一般认为是比指向const值的指针更好的方法

**2.对比输入与输出参数**  

```cpp
// Ex8_08.cpp
// 使用引用参数
#include <iostream>
#include <format>
#include <vector>
#include <string>

using std::string;
using std::vector;

void find_words(vector<string> &words, const string &str, const string &separators);
void list_words(const vector<string> &words);

int main()
{
    string text; // 要搜索的字符串
    std::cout << "Enter some text terminated by *:\n";
    std::getline(std::cin, text, '*');

    const string separators{" ,;:.\"!?'\n"}; // 单词分隔符
    vector<string> words;

    find_words(words, text, separators);
    list_words(words);
}

void find_words(vector<string> &words, const string &text, const string &separators)
{
    size_t start{text.find_first_not_of(separators)}; // 第一个单词的起始索引

    while (start != string::npos) // 查找单词
    {
        size_t end = text.find_first_of(separators, start + 1); // 查找单词的结尾
        if (end == string::npos)
            end = text.length();

        words.push_back(text.substr(start, end - start));    // 存储单词
        start = text.find_first_not_of(separators, end + 1); // 查找下一个单词的第一个字符
    }
}

void list_words(const vector<string> &words)
{
    std::cout << "Your string contains the following " << words.size() << " words:\n";
    size_t count{};
    for (const auto &word : words)
    {
        std::cout << std::format("{:>15}", word);
        if (!(++count % 5))
            std::cout << std::endl;
    }
    std::cout << std::endl;
}
```

上面示例程序的执行结果如下：

---

```cpp
Enter some text terminated by *:
Never judge a man until you have walked a mile in his shoes.
Then,who cares?He is a mile away and you have his shoes!*
Your string contains the following 26 words:
          Never          judge              a            man          until
            you           have         walked              a           mile
             in            his          shoes           Then            who
          cares             He             is              a           mile
           away            and            you           have            his
          shoes
```

---

- 输出参数：允许函数修改实参
- 输入参数：一般不允许修改实参，通常应该是对const值的引用
- 输入-输出参数：既是输入又是输出的参数，这种方式不好
- 可以将T值传递给T&和const T&引用，但是只能将const T值传递给const T&引用

**3.按引用传递数组**  

```cpp
double average10(const double (&array)[10])//Only arrays of length 10 be passed!
{
    double sum{};//Accumulate total in here
    for(size_t i{};i<10;++i)
        sum += array[i];//Sum array elements
    return sum / 10;//Return average
}
```

- 因为数组运算符[]比引用运算符&的优先级更高，所以把&括起来。可以是`const double (&array)[10]`，也可以是`const double (&array[10])`，但不能是`const double &array[10]`，因为后者表示10个`const double &`引用的数组
- 按引用传递数组，可以使用sizeof()、std::size()和基于范围的for循环等
- 现代C++更推荐使用`std::array<double, 10>`，避免复杂的数组引用语法。`double average10(const std::array<double,10>& value)`

```cpp
// Ex8_09A.cpp
// 按引用传递数组
#include <iostream>
#include <iterator>

double average10(const double (&array)[10]);

int main()
{
    double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average10(values) << std::endl;
}

double average10(const double (&array)[10])
{
    double sum{};
    for (size_t i{}; i < std::size(array); ++i)
        sum += array[i];
    return sum / std::size(array);
}
```

上面示例程序运行结果如下：

---

```cpp
Average = 5.5
```

---

```cpp
// Ex8_09B.cpp
// 按引用传递数组
#include <iostream>
#include <iterator>

double average10(const double (&)[10]);

int main()
{
    double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average10(values) << std::endl;
}

double average10(const double (&array)[10])
{
    double sum{};
    for (auto val : array)
        sum += val;
    return sum / std::size(array);
}
```

上面示例程序运行结果如下：

---

```cpp
Average = 5.5 
```

---

```cpp
// Ex8_09C.cpp
// 按引用传递数组，std::array<>方式
#include <iostream>
#include <array>

double average10(const std::array<double, 10> &);

int main()
{
    std::array<double, 10> values{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average10(values) << std::endl;
}

double average10(const std::array<double, 10> &array)
{
    double sum{};
    for (auto val : array)
        sum += val;
    return sum / array.size();
}
```

上面示例程序运行结果如下：

---

```cpp
Average = 5.5
```

---

**4.引用和隐式转换**  

- 按值传递实参的函数，会对不同类型的数据进行隐式转换
- 按引用传递实参，如果是const值，可以隐式转换（在内存某个位置创建临时值），如果是非const值，则不允许转换(不允许创建临时值，编译报错)

```cpp
// Ex8_10.cpp
// Implicit conversions of reference parameters
#include <iostream>

void double_it(double &it) { it *= 2; }
void print_it(const double &it) { std::cout << it << std::endl; }

int main()
{
    double d{123};
    double_it(d);
    print_it(d);

    int i{456};
    // double_it(i);
    /*
    提示两条错误：
    1.cannot bind non-const lvalue reference of type 'double&' to a value of type 'int'
    2.无法用 "int" 类型的值初始化 "double &" 类型的引用(非常量限定)
    */
    print_it(i);
}
```

上面示例程序运行结果如下：

---

```cpp
246
456
```

---

## 8.4默认实参值

1. 指定默认实参值的方式如下：  
`void show_error(std::string message="Program Error");`
2. 如果分别创建了函数原型和函数定义，则在函数原型中指定默认实参，而不是在函数定义中指定
3. 要输出默认消息，可以在调用函数时不指定对应的实参，要输出特定的消息，则指定实参
4. 给引用参数指定默认值的方式和按值传递实参的方式完全相同，但是对于引用非const值的参数是非法的，不能编译，如：  
`void show_error(std::string& message="Program Error");//非法`  
`void show_error(const std::string& message="Program Error");//合法`

**多个默认实参值**  

- 对于有默认值的参数，应把最不可能省略的参数放在前面，把最可能省略的放在最后
- 只能省略参数列表中最后的几个参数，不能跳着省略

```cpp
// Ex8_11.cpp
// Using multiple default parameter
#include <iostream>
#include <format>
#include <string>

void show_data(const int data[], size_t count = 1,
               const std::string &title = "Data Values",
               size_t width = 10, size_t perline = 5);

int main()
{
    int samples[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int dataItem{-99};
    show_data(&dataItem);

    dataItem = 13;
    show_data(&dataItem, 1, "Unlucky for some!");

    show_data(samples, std::size(samples));
    show_data(samples, std::size(samples), "Samples");
    show_data(samples, std::size(samples), "Samples", 6);
    show_data(samples, std::size(samples), "Samples", 8, 4);
}

void show_data(const int data[], size_t count,
               const std::string &title,
               size_t width, size_t perline)
{
    std::cout << title << std::endl;
    for (size_t i{}; i < count; ++i)
    {
        std::cout << std::format("{:{}}", data[i], width);
        if ((i + 1) % perline == 0)
            std::cout << '\n';
    }
    std::cout << std::endl;
}
```

上面示例程序运行结果如下：

---

```cpp
Data Values
       -99
Unlucky for some!
        13
Data Values
         1         2         3         4         5
         6         7         8         9        10
        11        12
Samples
         1         2         3         4         5
         6         7         8         9        10
        11        12
Samples
     1     2     3     4     5
     6     7     8     9    10
    11    12
Samples
       1       2       3       4
       5       6       7       8
       9      10      11      12
```

---

## 8.5 main()函数的实参

可以把函数main()定义为在运行程序时接收从命令行输入的实参。格式如下：  
`int main(int argc,char* argv[]) {//Code for main()...}`

1. 调用程序时使用的程序名总是在argv的第一个元素argv[0]中记录
2. argv中的最后一个元素（即argv[argc]）总是nullptr，因此argv中元素的个数是argc+1
3. 如何处理命令行实参完全取决于程序员，如下案例：

```cpp
// Ex8_12.cpp
// 命令行计算器：支持加减乘除
#include <iostream>
#include <cstdlib> // for atof()

int main(int argc, char *argv[])
{
    // 检查参数数量是否正确
    if (argc != 4)
    {
        std::cout << "用法: Ex8_12.exe <数字1> <运算符> <数字2>" << std::endl;
        std::cout << "示例: Ex8_12.exe 10 + 5" << std::endl;
        return 1; // 返回非零表示错误
    }

    // 解析参数
    double num1 = std::atof(argv[1]); // 字符串转浮点
    char op = argv[2][0];             // 运算符
    double num2 = std::atof(argv[3]);

    // 计算并输出结果
    double result;
    switch (op)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 == 0)
        {
            std::cout << "错误：除数不能为零！" << std::endl;
            return 1;
        }
        result = num1 / num2;
        break;
    default:
        std::cout << "不支持的运算符: " << op << std::endl;
        return 1;
    }

    std::cout << num1 << " " << op << " " << num2 << " = " << result << std::endl;
    return 0;
}
```

上面示例程序运行结果如下：

---

```cpp
ex8_12.exe 10 + 5
10 + 5 = 15
```

---
