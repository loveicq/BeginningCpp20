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

## 8.6 从函数中返回值

在指针返回到调用函数时，指针指向的变量必须仍在其作用域中。  
**不要从函数中返回在栈上分配的自动局部变量的地址。**  

```cpp
// Ex8_13.cpp
// Retruning a pointer
#include <iostream>
#include <format>
#include <array>
#include <string>

void show_data(const double data[], size_t count = 1,
               const std::string &title = "Data Values",
               size_t width = 10, size_t perLine = 5);
const double *largest(const double data[], size_t count);
const double *smallest(const double data[], size_t count);
double *shift_range(double data[], size_t count, double delta);
double *scale_range(double data[], size_t count, double divisor);
double *normalize_range(double data[], size_t count);

int main()
{
    double samples[]{
        11.0, 23.0, 13.0, 4.0,
        57.0, 36.0, 317.0, 88.0,
        9.0, 100.0, 121.0, 12.0};
    const size_t count{std::size(samples)};             // Number of samples
    show_data(samples, count, "Original Values");       // Output original values
    normalize_range(samples, count);                    // Normalize the values
    show_data(samples, count, "Normalized Values", 12); // Output normalized values
}

// Output an array of double values
void show_data(const double data[], size_t count,
               const std::string &title, size_t width, size_t perLine)
{
    std::cout << title << std::endl; // Display the title
    // Output the data value
    for (size_t i{}; i < count; ++i)
    {
        // Display a data item(uses a ddynamic field width:see Chapter 7)
        std::cout << std::format("{:{}.6g}", data[i], width);
        if ((i + 1) % perLine == 0)
            std::cout << '\n';
    }
    std::cout << std::endl;
}

const double *smallest(const double data[], size_t count)
{
    if (!count)
        return nullptr; // There is no smallest in an empty array

    size_t index_min{};
    for (size_t i{1}; i < count; ++i)
        if (data[index_min] > data[i])
            index_min = i;
    return &data[index_min];
}

double *shift_range(double data[], size_t count, double delta)
{
    for (size_t i{}; i < count; ++i)
        data[i] += delta;
    return data;
}

const double *largest(const double data[], size_t count)
{
    if (!count)
        return nullptr; // There is no largest in an empty array

    size_t index_max{};
    for (size_t i{1}; i < count; ++i)
        if (data[index_max] < data[i])
            index_max = i;

    return &data[index_max];
}

double *scale_range(double data[], size_t count, double divisor)
{
    if (!divisor)
        return data; // Do nothing for a zero divisor

    for (size_t i{}; i < count; ++i)
        data[i] /= divisor;
    return data;
}

double *normalize_range(double data[], size_t count)
{
    shift_range(data, count, -(*smallest(data, count)));
    return scale_range(data, count, *largest(data, count));
}
```

上面示例程序主要目的是对一组数据进行归一化处理，将数据映射到[0,1]区间。**归一化是数据预处理常用技术，方便不同量纲的数据进行比较或输入到机器学习模型中。** 程序运行结果如下：

---

```cpp
Original Values                                                               
        11        23        13         4        57                            
        36       317        88         9       100                            
       121        12                                                          
Normalized Values                                                             
   0.0223642   0.0607029    0.028754           0    0.169329                  
    0.102236           1    0.268371   0.0159744    0.306709                  
    0.373802   0.0255591 
```

---

### 8.6.2 返回引用

```cpp
std::string& larger(std::string& s1,std::string& s2)
{
    return s1>s2?s1:s2;//return a reference to the larger string
}
```

不要从函数中返回自动局部变量的引用  

如果要修改std::string变量的值，就不能定义为const  

如果是非const变量，就不能用字符串字面量来作实参。反之，如果要用字符串字面量做实参，就必须定义为const变量  

### 8.6.3 对比返回值与输出参数

1. 返回一个值  
`vector<std::string> find_words(const std::string& str,const std::string& separators);`
2. 将值放到输出参数中  
`void find_words(vector<std::string>& words,const std::string str,const std::string& separators);`

- 在现代C++中，一般应该首选返回值
- 数组或包含数组的对象是明显的例外，对于它们来说，使用输出参数仍然是更好的方案

### 8.6.4 返回类型推断

- 一定不要返回一个指向自动局部变量或临时对象的指针或引用
- auto不会推断为一个引用类型，而总是推断为一个值类型。要让编译器推断一个引用类型，可以使用auto&或const auto&
- 对局部变量使用auto时，上面的规则也适用

## 8.7 静态变量

用`static`关键字声明静态变量  

```cpp
unsigned int nextInteger()
{
    static unsigned int count {0};//声明静态变量
    return ++count;
}
```

- 只有第一次执行包含`static`的语句时，才会创建变量并初始化，后面再执行该语句就没有效果了
- 如果不初始化静态变量，默认初始化为0
- 普通变量不初始化，将包含垃圾值，而不是0

## 8.8 函数重载

1. 编译器通过函数的签名来区分函数，函数的签名是函数名及其参数列表的组合
2. 重载函数的名称相同，所以每个重载函数的签名必须有不同的参数列表
    - 函数的参数个数不同
    - 至少有一对对应参数的类型不同
3. 函数的返回类型不是函数签名的一部分。如果声明了两个同名的函数，参数列表也相同，只是返回类型不同，程序将无法编译

```cpp
// Ex8_14.cpp
// Overloading a function
#include <iostream>
#include <string>
#include <vector>

// Function prototypes
double largest(const double data[], size_t count);
double largest(const std::vector<double> &data);
int largest(const std::vector<int> &data);
std::string largest(const std::vector<std::string> &words);
/*Above function overload would not compile:overloaded function
must differ in more than just their return type!*/

int main()
{
    double array[]{1.5, 44.6, 13.7, 21.2, 6.7};
    std::vector<int> numbers{15, 44, 13, 21, 6, 8, 5, 2};
    std::vector<double> data{3.5, 5, 6, -1.2, 8.7, 6.4};
    std::vector<std::string> names{"Charles Dickens", "Emily Bronte",
                                   "Jane Austen", "Henry James", "Arthur Miller"};
    std::cout << "The largest of array is " << largest(array, std::size(array)) << std::endl;
    std::cout << "The largest of numbers is " << largest(numbers) << std::endl;
    std::cout << "The largest of data is " << largest(data) << std::endl;
    std::cout << "The largest of words is " << largest(names) << std::endl;
}

// Finds the largest of an array of double values
double largest(const double data[], size_t count)
/*data[]会自动退化为指向数组第一个元素的指针，所以不用引用。
但编译时必须知道元素数量，所以参数count不可少*/
{
    double max{data[0]};
    for (size_t i{1}; i < count; ++i)
        if (max < data[i])
            max = data[i];
    return max;
}

// Finds the largest of a vector of double values
double largest(const std::vector<double> &data)
{
    double max{data[0]};
    for (auto value : data)
        if (max < value)
            max = value;
    return max;
}

// Finds the largest of a vector of int values
int largest(const std::vector<int> &data)
{
    int max{data[0]};
    for (auto value : data)//这里不用&，是因为value是基本类型int，复制开销小
        if (max < value)
            max = value;
    return max;
}

// Finds the largest of a vector of string objects
std::string largest(const std::vector<std::string> &words)
{
    std::string max_word{words[0]};
    for (const auto &word : words)//这里用&，是因为string类型，复制开销大，故引用之
        if (max_word < word)
            max_word = word;
    return max_word;
}
```

上面示例程序运行结果如下：  

---

```cpp
The largest of array is 44.6
The largest of numbers is 44
The largest of data is 8.7
The largest of words is Jane Austen 
```

---

上面这个示例的多个largest()函数有相同的实现，为避免代码重复，应使用**函数模板**。  

### 8.8.1 重载和指针参数

```cpp
int largest(int* pValues,size_t count);//Prototype 1
int largest(float* pValues,size_t count);//Prototype 2
int largest(int values[],size_t count);//Identical signature to prototype 1
int largest(int values[100],size_t count);//Identical signature to prototype 1
//第1和第3、4个函数是相同的重载函数（不能同时存在，否则无法编译），和第2是不同的重载函数（可以同时存在）
```

### 8.8.2 重载和引用参数

不能把参数类型是data_type的函数，重载为参数类型是data_type&的函数，如下：

```cpp
void do_it(std::string number);//These are not distinguishable...
void do_it(std::string& number);//...from the argument type
```

```cpp
// Ex8_15.cpp
// Overloading a function with reference parameters
#include <iostream>
#include <format>

double larger(double a, double b); // Non-reference parameters
long &larger(long &a, long &b);    // Reference parameters

int main()
{
    double a_double{1.5}, b_double{2.5};
    std::cout << std::format("The larger of double values {} and {} is {}\n",
                             a_double, b_double, larger(a_double, b_double));

    int a_int{15}, b_int{25};
    std::cout << std::format("The larger of int values {} and {} is {}\n",
                             a_int, b_int,
                             larger(static_cast<long>(a_int), static_cast<long>(b_int)));
}

//Returns the larger of two floating point values
double larger(double a,double b)
{
    std::cout<<"double larger() called."<<std::endl;
    return a>b?a:b;
}

//Returns the larger of two long references
long& larger(long& a,long& b)
{
    std::cout<<"long ref larger() called"<<std::endl;
    return a>b?a:b;
}
```

上面示例程序运行结果如下：

---

```cpp
double larger() called.
The larger of double values 1.5 and 2.5 is 2.5
double larger() called.
The larger of int values 15 and 25 is 25
```

---

**注意：**  

1. `static_cast<long>()`创建临时地址，编译器不会使用临时地址来初始化非const值的引用，所以会调用`double larger(double a, double b)`函数而不是`long &larger(long &a, long &b)`函数

2. 如果要引用调用long&类型的函数，可以把形参声明为const引用：`long larger(const long& a,const long& b);`，因为C++可以const& 临时地址。如果非要返回long&，则函数返回值前面也要加上const：`const long& larger(const long& a,const long& b);`

### 8.8.3 重载和const参数

1. 实参在按值传递时，在函数原型中把参数指定为const是没有意义的，因为传递的是副本，不会修改实参的初始值
2. 实参在按引用或按指针传递时，会有区别：  

    **重载和const指针参数**  

    - 一个函数参数类型是type*，另一个函数的参数类型是const type*，这两个函数就是不同的

    ```cpp
    //Prototype1
    long* larger(long* a,long* b);
    //Protoytpe2
    const long* larger(const long* a,const long* b);
    ```

    - 编译器不会把const值传递给带非const指针参数的函数

    ```cpp
    long num1{1L};
    long num2{2L};
    long num3{*larger(&num1,&num2)};//调用Prototype1，注意函数前的*是解引用的意思，因为函数原型是返回指针

    const long num4{1L};
    const long num5{2L};
    const long num6{*larger(&num4,&num5)};//调用Protoytpe2，注意函数前的*是解引用的意思，因为函数原型是返回指针
    ```

    - 在函数原型中的星号后面添加const修饰符没有意义，只有在函数定义中才应该考虑这么做  

    ```cpp
    //与prototype1相同
    long* larger(long* const a,long* const b);
    //与prototype2相同
    const long* larger(const long* const a,const long* const b);
    ```

    **重载和const引用参数**

    - 不允许在&符号后添加const  
    - T&和const T&总是不同的

### 8.8.4 重载和默认实参值

对于重载函数，默认实参值有时会影响编译器区分函数调用的能力

## 8.9 递归

在函数包含对自身的调用时，该函数就称为递归函数。使用递归可有效地遍历组织为树的数据。

### 8.9.1 基本示例

```cpp
// Ex8_16.cpp
// Recursive version of function for x to the power n, n positive or negative
#include <iostream>
#include <format>

double power(double x, int n);

int main()
{
    for (int i{-3}; i <= 3; ++i) // Calculate powers of 8 from -3 to +3
        std::cout << std::format("{:10g}", power(8.0, i));
    std::cout << std::endl;
}

// Recursive function to calculate x to the power n
double power(double x, int n)
{
    if (n == 0)
        return 1.0;
    else if (n > 0)
        return x * power(x, n - 1);
    else // n<0
        return 1.0 / power(x, -n);
}
```

上面示例程序运行结果如下：

---

```cpp
0.00195312  0.015625     0.125         1         8        64       512 
```

---

使用递归，需要确保解决问题所需的递归深度本身不会成为问题。

### 8.9.2 递归算法

递归常常用于实现排序和合并操作  

**1.快速排序算法**  

首先从单词集合中任意选择一个单词，然后安排剩余单词的位置，把所有小于所选单词的单词放在所选单词的左边，把所有大于所选单词的单词放在所选单词的右边，所选单词左右两边的单词不必按顺序排序。对越来越小的单词集合执行相同的过程，直到每个单词都位于一个独立的集合中为止。  
应采用std::string对象的智能指针来存储单词，并将这些指针存储在一个向量容器中。  

**2.main()函数**  

```cpp
// Ex8_17.cpp
//  Sorting words recursively
#include <iostream>
#include <format>
#include <memory>
#include <vector>

using Words = std::vector<std::shared_ptr<std::string>>;

void swap(Words &words, size_t first, size_t second);
void sort(Words &words);
void sort(Words &words, size_t start, size_t end);
void extract_words(Words &words, const std::string &text, const std::string &separators);
void show_words(const Words &words);
size_t max_word_length(const Words &words);

int main()
{
    Words words;
    std::string text;                   // The string to be sorted
    const auto separators{" ,.!?\"\n"}; // Word delimiters

    // Read the string to be processed from the dkyboard
    std::cout << "Enter a string terminated by *:" << std::endl;
    getline(std::cin, text, '*');
    extract_words(words, text, separators);
    if (words.empty())
    {
        std::cout << "No words in text." << std::endl;
        return 0;
    }

    sort(words);       // Sort the words
    show_words(words); // Output the words
}

void extract_words(Words &words, const std::string &text, const std::string &separators)
{
    size_t start{text.find_first_not_of(separators)}; // Start index of first word

    while (start != std::string::npos)
    {
        size_t end = text.find_first_of(separators, start + 1); // Find end of a word
        if (end == std::string::npos)
            end = text.length();
        words.push_back(std::make_shared<std::string>(text.substr(start, end - start)));
        start = text.find_first_not_of(separators, end + 1); // Find start next word
    }
}

void swap(Words &words, size_t first, size_t second)
{
    auto temp(words[first]);
    words[first] = words[second];
    words[second] = temp;
}

void sort(Words &words, size_t start, size_t end)
{
    // start index must be less than end index for 2 or more elements
    if (!(start < end))
        return;

    // Choose middle address to partition set
    swap(words, start, (start + end) / 2); // Swap middle address with start

    // Check words against chosen word
    size_t current{start};
    for (size_t i{start + 1}; i <= end; i++)
    {
        if (*words[i] < *words[start]) // Is word less than chosen word?
            swap(words, ++current, i); // Yes,so swap to the left
    }

    swap(words, start, current); // Swap chosen and last swapped words
    if (current > start)
        sort(words, start, current - 1); // Sort left subset if exists
    if (end > current + 1)
        sort(words, current + 1, end); // Sort right subset if exists
}

// Sort strings in ascending sequence
void sort(Words &words)
{
    if (!words.empty())
        sort(words, 0, words.size() - 1);
}

size_t max_word_length(const Words &words)
{
    size_t max{};
    for (auto &pword : words)
        if (max < pword->length())
            max = pword->length();
    return max;
}

void show_words(const Words &words)
{
    const size_t field_width{max_word_length(words) + 1};
    const size_t words_per_line{8};
    std::cout << std::format("{:{}}", *words[0], field_width); // Output first word

    size_t words_in_line{}; // Number of words in current line
    for (size_t i{1}; i < words.size(); ++i)
    {
        // Output newline when initial letter changes or after 8 per line
        if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
        {
            words_in_line = 0;
            std::cout << std::endl;
        }
        std::cout << std::format("{:{}}", *words[i], field_width); // Output a word
    }
    std::cout << std::endl;
}
```

上面示例程序运行结果如下：

---

```cpp
Enter a string terminated by *:
It was the best of times , it was the worst of times , it was the age of wisdom , it was the age of foolishness , it was the epoch of belief , it was the epoch of incredulity , it was the season of Light , it was the season of Darkness , it was the spring of hope , it was the winter of despar , we had everything before us , we had nothing before us , we were all going direct to Heaven , we were all going direct the other way - in short , the period was so far like the preent period , that some of its noisiest authorities insisted on its being received , for good or for evil , in the superlative degree of comparison only .*

Darkness
Heaven
It
Light
age         age         all         all         authorities 
before      before      being       belief      best        
comparison  
degree      despar      direct      direct      
epoch       epoch       everything  evil        
far         foolishness for         for         
going       going       good        
had         had         hope        
in          in          incredulity insisted    it          it          it          it          
it          it          it          it          it          its         its         
like        
noisiest    nothing     
of          of          of          of          of          of          of          of          
of          of          of          of          on          only        or          other       
period      period      preent      
received    
season      season      short       so          some        spring      superlative 
that        the         the         the         the         the         the         the         
the         the         the         the         the         the         the         times       
times       to          
us          us          
was         was         was         was         was         was         was         was         
was         was         was         way         we          we          we          we          
were        were        winter      wisdom      worst       
```

---

## 8.10 本章小结

## 8.11 练习

1. 第1题

    ```cpp

    /*************************第8章_练习_第1题************************
    编写一个函数validate_input()，它接收两个整数实参，表示所输入整数的上
    下限。它接收的第三个实参是描述输入的字符串，用于提示用户进行输入。该函
    数会提示所输入的值应在前两个实参指定的范围内，并包含标识输入值类型的字
    符串。该函数应检查输入并一直提示用户输入值，直到输入的值有效为止。在程
    序中使用validate_input()函数，获取用户的生日并以下面的格式输出：
    You were born on the 21st of November,2012
    这个程序应使各个函数month()、year()和day()管理对应数字的输入，不要忘
    了闰年。2017年2月29日是不允许输入的。
    *****************************************************************/

    #include <iostream>
    #include <format>
    #include <string>

    int validate_input(int lower, int upper, const std::string &description);
    int year();
    int month();
    int date(int month_value, int year_value);
    std::string ending(int date_day);

    int main()
    {
        std::cout << "Enter your date of borth." << std::endl;
        int date_year{year()};
        int date_month{month()};
        int date_day{date(date_month, date_year)};

        std::string months[]{"January", "February", "March",
                            "April", "May", "June",
                            "July", "August", "September",
                            "October", "November", "December"};

        std::cout << std::endl;
        std::cout << std::format("You were born on the {} of {}, {}.",
                                std::to_string(date_day) + ending(date_day),
                                months[date_month - 1],
                                date_year)
                << std::endl;
    }

    // 读取一个介于最小值和最大值之间的整数
    int validate_input(int lower, int upper, const std::string &description)
    {
        int data{};
        std::cout << std::format("Please enter {} from {} to {}: ", description, lower, upper);
        std::cin >> data;
        while (data < lower || data > upper)
        {
            std::cout << "Invalid entry; please re-enter " << description << ": ";
            std::cin >> data;
        }

        return data;
    }

    // 读取年份
    int year()
    {
        const int low_year{1870};
        const int high_year{2020};
        return validate_input(low_year, high_year, "a year");
    }

    // 读取月份
    int month()
    {
        const int low_month{1};
        const int high_month{12};
        return validate_input(low_month, high_month, "a month number");
    }

    // 读取给定年份和月份的日期
    int date(int month, int year)
    {
        const int date_min{1};
        const int feb{2};

        // Days in month:           Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
        static const int date_max[]{31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
        /*由于上面的数组被声明为静态，它只会在函数第一次被调用时被创建。当然，在这个例子中
        ，这并没有保存任何东西，因为我们只调用它一次…*/

        // 闰年的二月有29天。闰年是指能被4整除的年份，但能被100整除而不能被400整除的年份除外。
        if (month == feb && year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0))
            return validate_input(date_min, 29, "a date");
        else
            return validate_input(date_min, date_max[month - 1], "a date");
    }

    /*如果数字结尾是：
    ├─ 1 → st  (1st, 21st, 31st...)
    ├─ 2 → nd  (2nd, 22nd...)
    ├─ 3 → rd  (3rd, 23rd...)
    └─ 4,5,6,7,8,9,0 → th  (4th, 15th, 26th, 30th...)

    但 11, 12, 13 例外，都用 th！
    加后缀都是英文日期的习惯表示法而已*/
    std::string ending(int date_day)
    {
        if (date_day == 1 || date_day == 21 || date_day == 31)
            return "st";
        else if (date_day == 2 || date_day == 22)
            return "nd";
        else if (date_day == 3 || date_day == 23)
            return "rd";
        else
            return "th";
    }

    ```

    上面示例程序的运行结果如下：

    ---

    ```cpp
    Enter your date of borth.                                                                                                  
    Please enter a year from 1870 to 2020: 1984                                                                                
    Please enter a month number from 1 to 12: 4                                                                                
    Please enter a date from 1 to 30: 30                                                                                       
                                                                                                                            
    You were born on the 30th of April, 1984.  
    ```

    ---

2. 第2题

    ```cpp
    /*************************第8章_练习_第2题************************
    编写一个函数，要求读取字符串或字符数组作为输入，并反转它的顺序。使用什
    么类型的参数最好？用main()函数测试该函数，提示用户输入一个字符串，反
    转其顺序，再输出反转后的字符串。
    注意：“反转其顺序”即指改变原字符串，所以需要用指针或引用，不能按值传递
    *****************************************************************/
    #include <iostream>
    #include <string>
    #include <format>

    std::string reverse(std::string str);

    int main()
    {
        std::string sentence;

        std::cout << "Enter a sequence of characters, then press 'Enter': " << std::endl;
        std::getline(std::cin, sentence);
        std::cout << std::format("Your sequence in reverse order is:\n{}\n", reverse(sentence)) << std::endl;

        std::cout << "Here is a demonstration of reverse() working with a C-style string:" << std::endl;

        char stuff[]{"abcdefg"}; // C-style string
        std::cout << std::format("The original string is: \"{}\"\nReversed it becomes: \"{}\"",
                                stuff, reverse(stuff))
                << std::endl;
    }
    std::string reverse(std::string str)
    {
        const size_t length{str.length()};
        for (size_t i{}; i < length / 2; ++i)
        {
            char temp = str[i];
            str[i] = str[length - i - 1];
            str[length - i - 1] = temp;
        }
        return str;
    }
    ```

    上面示例程序运行结果如下：

    ---

    ```cpp
    Enter a sequence of characters, then press 'Enter': 
    Hello,world!
    Your sequence in reverse order is:
    !dlrow,olleH

    Here is a demonstration of reverse() working with a C-style string:
    The original string is: "abcdefg"
    Reversed it becomes: "gfedcba"
    ```

    ---

3. 第3题

    ```cpp
    /*************************第8章_练习_第3题************************
    编写一个程序，它接收2~4个命令行实参。如果用少于2个或多于4个的实参调用
    该程序，就输出一条消息，告诉用户应怎么做，然后退出。如果实参的个数是正
    确的，就输出它们，一行输出一个参数。
    注：命令行实参指的是main()函数的实参，详见本章第8.5节
    *****************************************************************/
    #include <iostream>

    int main(int argc, char *argv[])
    {
        if (argc < 3 || argc > 4)
            std::cout << "参数错误，请输入2~4个参数！" << std::endl;
        else
            for (int i{1}; i < argc; ++i) // 不用输出程序名称:argv[0]
                std::cout << "参数 " << i << " 是 " << argv[i] << std::endl;
    }
    ```

    上面示例程序运行结果如下：

    ---

    ```cpp
    C:\exer8_03 a.exe      
    参数错误，请输入2~4个参数！

    C:\exer8_03 a.exe b.com
    参数 1 是 a.exe
    参数 2 是 b.com
    ```

    ---

4. 第4题

    ```cpp
    /*************************第8章_练习_第4题************************
    创建一个函数plus()，它把两个数值加在一起，返回它们的和。提供处理int、
    double和string类型的重载版本，测试它们是否能处理下面的调用：
    const int n {plus(3,4)};
    const double d {plus(3.2,4.2)};
    const string s {plus("he","llo")};
    const string s1 {"aaa"};
    const string s2 {"bbb"};
    const string s3 {plus(s1,s2)};
    为什么下面的调用不工作？
    const auto d {plus(3,4.2)};
    *****************************************************************/
    #include <iostream>
    #include <string>

    int add(int a, int b);
    double add(double a, double b);
    std::string add(const std::string &str1, const std::string &str2);
    // 记得std::string类型要用&!!!

    int main()
    {
        const int n{add(3, 4)};
        const double d{add(3.2, 4.2)};
        const std::string s{add("he", "llo")};

        const std::string s1{"aaa"};
        const std::string s2{"bbb"};
        const std::string s3{add(s1, s2)};

        // const auto d{add(3, 4.2)};//参数类型不匹配任何重载版本

        std::cout << "add(3, 4) = " << n << std::endl;
        std::cout << "add(3.2, 4.2) = " << d << std::endl;
        std::cout << "add(\"he\",\"llo\") = " << s << std::endl;
        std::cout << "当变量s1 = \"aaa\"，变量s2 = \"bbb\"时，";
        std::cout << "add(s1, s2) = " << s3 << std::endl;
    }

    int add(int a, int b) { return a + b; }

    double add(double a, double b) { return a + b; }

    std::string add(const std::string &str1, const std::string &str2) { return str1 + str2; }
    ```

    以上示例程序运行结果如下：

    ---

    ```cpp
    add(3, 4) = 7
    add(3.2, 4.2) = 7.4
    add("he","llo") = hello
    当变量s1 = "aaa"，变量s2 = "bbb"时，add(s1, s2) = aaabbb
    ```

    ---

5. 第5题

    ```cpp
    /*************************第8章_练习_第5题************************
    定义一个函数，检查给定数字是不是质数。不要求检查质数的代码很高效；读者
    能够想到的任何算法都可接受。这里重新说明一下，质数是比1大的自然数，除了
    1和自身之外，不能被其他正数整除。编写另一个函数，使其生成一个vector<>，
    该vector<>中包含从一个数字开始，小于或等于另一个数字的所有自然数。默认
    情况下应该从1开始。创建第三个函数，它接收一个数字vector<>作为参数，输
    出另一个vector<>，其中包含在输入中找到的所有质数。使用这三个函数创建一
    个程序，输出小于或等于用户选择的数字的所有质数（例如，每行输出15个质数）
    。注意，原则上，要输出这些质数，并不需要任何vector对象；显然，添加这些
    函数只是为了帮助读者多加练习。
    *****************************************************************/
    #include <iostream>
    #include <vector>
    #include <string>
    #include <format>

    int check_prime_numbers(int num);
    std::vector<int> generate_natural_numbers(int startNum = 1, int endNum = 10);
    std::vector<int> filter_primes(const std::vector<int> &naturalNumberVec);
    void printNum(const std::vector<int> &primesNum, size_t numPerline);

    int main()
    {
        int lowerNum{}, maxNum{};
        std::cout << "自然数序列，请输入最小和最大的整数，以空格隔开：";
        std::cin >> lowerNum >> maxNum;
        while (lowerNum <= 1 || maxNum < lowerNum)
        {
            std::cout << "最小数必须 > 1，且最大数必须 >= 最小数：";
            std::cin >> lowerNum >> maxNum;
        }

        std::vector<int> naturalNums{generate_natural_numbers(lowerNum, maxNum)};
        std::vector<int> primeNums{filter_primes(naturalNums)};

        size_t perline{};
        std::cout << "请输入每行要输出的质数个数：";
        std::cin >> perline;
        printNum(primeNums, perline);
    }

    int check_prime_numbers(int num)
    {
        if (num <= 1)
            return 0; // 质数必须大于1，虽然main()中已排队num<=1了
        if (num == 2)
            return 1; // 2是唯一的偶质数
        if (num % 2 == 0)
            return 0; // 偶数(除了2)都不是质数
        for (int i{3}; i * i <= num; i += 2)
            // i*i<=num条件原理：所有因数对都以sqrt(num)为分界线，左边的都≤sqrt(num)，右边的都≥sqrt(num)
            // 如果是i<num条件，效率较低。而且绝对不能是i<=num，否则num%i==0，num是质数也会返回0
            if (num % i == 0)
                return 0;

        return 1;
    }

    std::vector<int> generate_natural_numbers(int startNum, int endNum)
    {
        std::vector<int> naturalNumberVec;
        for (int i{startNum}; i <= endNum; ++i)
            naturalNumberVec.push_back(i);
        return naturalNumberVec;
    }

    std::vector<int> filter_primes(const std::vector<int> &naturalNumberVec)
    {
        std::vector<int> primeVec;
        for (auto a : naturalNumberVec)
            if (check_prime_numbers(a))
                primeVec.push_back(a);
        return primeVec;
    }

    void printNum(const std::vector<int> &primesNum, size_t numPerline)
    {
        if (primesNum.empty())
            return;

        int count_digits{static_cast<int>(std::to_string(primesNum.back()).length()) + 3};
        // 用于控制输出列宽。primeNum已经是有序的，最后一个就是最大数
        size_t perLine{}; // 每行输出个数

        for (auto num : primesNum)
        {
            std::cout << std::format("{:>{}}", num, count_digits);
            if (++perLine == numPerline)
            {
                std::cout << std::endl;
                perLine = 0;
            }
        }
        std::cout << std::endl;
    }
    ```

    以上示例程序运行结果如下：

    ---

    ```cpp
    自然数序列，请输入最小和最大的整数，以空格隔开：1 100
    最小数必须 > 1，且最大数必须 >= 最小数：-100 100
    最小数必须 > 1，且最大数必须 >= 最小数：100 2
    最小数必须 > 1，且最大数必须 >= 最小数：2 100
    请输入每行要输出的质数个数：10
     2    3    5    7   11   13   17   19   23   29
    31   37   41   43   47   53   59   61   67   71
    73   79   83   89   97
    ```

    ---

6. 第6题

    ```cpp
    /*************************第8章_练习_第6题************************
    编写一个程序，请示用户输入多个成绩。成绩是0~100之间的一个整数（包括0和
    100在内）。收集了所有成绩后，程序将输出以下数据：最高的5个成绩，最低的
    5个成绩，平均成绩，中值成绩，以及成绩的标准差和方差。当然，需要为计算
    每个统计数据分别编写函数。另外，代码只能输出5个值一次。为了进行练习，
    使用数组来存储5个极值，而不使用vector对象。注意，作为一个预处理步骤，
    应该首先对用户输入的成绩排序；之后，编写函数来计算统计数据就简单多了。
    可以通过调整EX8_17.cpp中的快速排序算法来处理成绩数字。一定要合理地处
    理用户输入的成绩少于5个（甚至没有输入成绩）的情况。怎么处理都可以，只
    要保证程序不崩溃即可。中值是出现在排序列表中间位置的值。如果成绩的个数
    是偶数，显然没有单独的一个中间值。此时，将中值定义为两个中间值的平均值。
    计算n个成绩xᵢ的中值（μ）和标准差（σ）的公式如下所示：
    μ=1/n∑_{i=0}^{n-1}xᵢ         σ=√(1/n∑_{i=0}^{n-1}(xᵢ-μ)²)
    方差被定义为σ²。标准库的<cmath>模块中定义了用于计算平方根的
    std::sqrt()函数。
    *****************************************************************/
    #include <iostream>
    #include <cmath>
    #include <vector>
    #include <string>

    void inputGrades(std::vector<int> &grades);
    void sortGrades(std::vector<int> &grades);
    void sortGrades(std::vector<int> &grades, int left, int right);
    void getGradeValues(
        std::vector<int> &grades,
        int TOPscores[],
        int LOWscores[],
        const size_t size,
        double *gradeAverage,
        double *gradeMiddle,
        double *gradeVariance,
        double *gradeStdDev);

    int main()
    {
        std::vector<int> all_grades;
        // 输入成绩
        inputGrades(all_grades);
        if (all_grades.size() < 5)
            return 1; // 输入的成绩数据不满足要求

        // 成绩从小到大排序
        sortGrades(all_grades);

        // 输出全部成绩
        // for (auto a : all_grades)
        //     std::cout << a << std::endl;

        const size_t size{5};
        int top5grades[size]{};    // 最高的5个成绩
        int bottom5grades[size]{}; // 最低的5个成绩
        double gradeAverage{};     // 平均成绩
        double gradeMiddle{};      // 中值成绩
        double gradeVariance{};    // 成绩方差
        double gradeStdDev{};      // 成绩标准差

        // 计算题目要求的各项数据
        getGradeValues(
            all_grades,
            top5grades,
            bottom5grades,
            size,
            &gradeAverage,
            &gradeMiddle,
            &gradeVariance,
            &gradeStdDev);

        // 输出题目要求的各项数据
        std::cout << "\n前5名成绩为：\n";
        for (size_t i{}; i < size; ++i)
            std::cout << top5grades[i] << std::endl;

        std::cout << "后5名成绩为：\n";
        for (size_t i{}; i < size; ++i)
            std::cout << bottom5grades[i] << std::endl;

        std::cout << "平均成绩是：" << gradeAverage << std::endl;
        std::cout << "中值成绩是：" << gradeMiddle << std::endl;
        std::cout << "成绩方差是：" << gradeVariance << std::endl;
        std::cout << "成绩标准差是：" << gradeStdDev << std::endl;
    }

    void inputGrades(std::vector<int> &grades)
    {
        int grade{};

        while (true)
        {
            std::cout << "请输入成绩(0~100)，输入‘#’结束：";
            if (std::cin >> grade)
            {
                if (grade >= 0 && grade <= 100)
                    grades.push_back(grade);
                else
                    std::cout << "无效成绩，请输入0~100之间的整数！" << std::endl;
            }
            else
            {
                char ch{};
                std::cin.clear(); // 清除错误的状态
                std::cin >> ch;
                if (ch == '#')
                    break;
                else
                    std::cout << "输入无效，请输入整数或‘#’结束！" << std::endl;
            }
        }
    }

    void sortGrades(std::vector<int> &grades)
    {
        if (grades.empty())
        {
            std::cout << "你没输入成绩，程序即将退出！" << std::endl;
            return;
        }

        sortGrades(grades, 0, static_cast<int>(grades.size()) - 1);
    }

    void sortGrades(std::vector<int> &grades, int left, int right)
    {
        // 递归终止条件
        if (left >= right)
            return;

        // 选择基准（中间位置的元素）
        int pivot{grades[(left + right) / 2]};

        // 分区
        int i{left}, j{right};
        while (i <= j)
        {
            // 从左找第一个 >= pivot的元素
            while (grades[i] < pivot)
                i++;
            // 从右找第一个 <= pivot的元素
            while (grades[j] > pivot)
                j--;

            if (i <= j)
            {
                // 交换数据
                int temp{grades[i]};
                grades[i] = grades[j];
                grades[j] = temp;
                // 继续移动指针
                i++;
                j--;
            }
        }

        // 递归排序左右两部分
        sortGrades(grades, left, j);  // 左半部分
        sortGrades(grades, i, right); // 右半部分
    }

    void getGradeValues(
        std::vector<int> &grades,
        int TOPscores[],
        int LOWscores[],
        const size_t size,
        double *gradeAverage,
        double *gradeMiddle,
        double *gradeVariance,
        double *gradeStdDev)
    {
        int socoreNum{static_cast<int>(grades.size())};

        // 计算前、后五名成绩并填充数组
        for (size_t i{}; i < size; ++i)
        {
            LOWscores[i] = grades[i];
            TOPscores[i] = grades[socoreNum - size + i];
        }

        // 计算平均成绩
        int totalGrade{};
        for (auto a : grades)
            totalGrade += a;
        *gradeAverage = totalGrade / socoreNum;

        // 计算中值成绩
        if (!(socoreNum % 2))
            *gradeMiddle = grades[socoreNum / 2];
        else
            *gradeMiddle = (grades[socoreNum / 2 - 1] + grades[socoreNum / 2]) / 2;

        // 计算标准差
        double sumStdDev{};
        for (int a : grades)
            sumStdDev = (a - *gradeAverage) * (a - *gradeAverage);
        *gradeStdDev = std::sqrt(sumStdDev / socoreNum);

        // 计算方差
        *gradeVariance = *gradeStdDev * *gradeStdDev;
    }
    ```

    以上示例程序运行结果如下：

    ---

    ```cpp
    请输入成绩(0~100)，输入‘#’结束：85
    请输入成绩(0~100)，输入‘#’结束：92
    请输入成绩(0~100)，输入‘#’结束：78
    请输入成绩(0~100)，输入‘#’结束：65
    请输入成绩(0~100)，输入‘#’结束：45
    请输入成绩(0~100)，输入‘#’结束：98
    请输入成绩(0~100)，输入‘#’结束：73
    请输入成绩(0~100)，输入‘#’结束：81
    请输入成绩(0~100)，输入‘#’结束：69
    请输入成绩(0~100)，输入‘#’结束：55
    请输入成绩(0~100)，输入‘#’结束：88
    请输入成绩(0~100)，输入‘#’结束：77
    请输入成绩(0~100)，输入‘#’结束：91
    请输入成绩(0~100)，输入‘#’结束：62
    请输入成绩(0~100)，输入‘#’结束：58
    请输入成绩(0~100)，输入‘#’结束：#

    前5名成绩为：
    85
    88
    91
    92
    98
    后5名成绩为：
    45
    55
    58
    62
    65
    平均成绩是：74
    中值成绩是：75
    成绩方差是：38.4
    成绩标准差是：6.19677
    ```

    ---

7. 第7题

    ```cpp
    /*************************第8章_练习_第7题************************
    计算机科学家介绍递归时介绍递归时，非常喜欢使用所谓的斐波那契函数。斐波那契函
    数计算著名的斐波那契数列中的第n个值。这是一个正整数序列，其特征是前两个数字
    之后的每个数字都是之前的两个数字之和。对于n≥1,该序列的定义如下：
    1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181...
    为便于使用，计算机科学家还定义了一个额外的第0个斐波那契数字，其值为0。编写一
    个函数来递归地计算第n个斐波那契数字。使用一个简单的程序来测试该函数，让用户决
    定要计算多少个数字，然后逐个输出每个数字，并将每个数字显示在单独的一行中。
    虽然斐波那契函数的朴素递归版本很优雅，几乎与其数学定义完全对应，但是执行速度很
    慢。如果让计算机计算100个斐波那契数字，你会注意到随着n越来越大，计算速度越来越
    慢。你是否能够重写这个函数来使用循环而不是递归？现在能够正确地计算多少个数字？
    注意，在循环的每次迭代中，自然会想计算下一个数字。这只需要前两个数字。因此，没
    有必要在一个vector<>中记录完整的序列。
    *****************************************************************/
    #include <iostream>
    #include<chrono>//计时

    long long fibonacci_recursive(size_t n);
    long long fibonacci_iterative(size_t n);

    int main()
    {
        size_t count{};//要输出的斐波那契数字个数
        std::cout<<"要计算多少个斐波那契数?[0~92]:";
        std::cin>>count;

        //递归计算
        {auto start{std::chrono::high_resolution_clock::now()};//开始时间
        std::cout<<"\n递归版本结果：\n";
        for(size_t i{1};i<=count;++i)
            std::cout<<"F("<<i<<") = "<<fibonacci_recursive(i)<<std::endl;
        auto end{std::chrono::high_resolution_clock::now()};//结束时间
        auto duration{std::chrono::duration_cast<std::chrono::milliseconds>(end-start)};
        std::cout<<"\n递归版本耗时："<< duration.count()<<" 毫秒。"<<std::endl;}

        //循环计算
        {auto start{std::chrono::high_resolution_clock::now()};//开始时间
        std::cout<<"\n循环版本结果：\n";
        for(size_t i{1};i<=count;++i)
            std::cout<<"F("<<i<<") = "<<fibonacci_iterative(i)<<std::endl;
        auto end{std::chrono::high_resolution_clock::now()};//结束时间
        auto duration {std::chrono::duration_cast<std::chrono::microseconds>(end-start)};
        std::cout<<"\n循环版本耗时："<< duration.count()<<" 微秒。"<<std::endl;}

    }

    long long fibonacci_recursive(size_t n)
    {
        if(n==0) return 0;
        if(n==1) return 1;
        //最后一个数等于前两个数相加，前两个数又分别用递归求得
        return fibonacci_recursive(n-1)+fibonacci_recursive(n-2);//最终只返回一个数
    }

    long long fibonacci_iterative(size_t n)
    {
        if(n==0) return 0;
        if(n==1) return 1;

        long long prev2{0};
        long long prev1{1};
        long long current;

        for(size_t i{2};i<=n;++i)
        {
            current=prev1+prev2;
            prev2=prev1;
            prev1=current;
        }

        return current;
    }
    ```

    以上示例程序运行结果如下：

    ---

    ```cpp
    要计算多少个斐波那契数?[0~92]:40

    递归版本结果：
    F(1) = 1
    F(2) = 1
    F(3) = 2
    F(4) = 3
    F(5) = 5
    F(6) = 8
    F(7) = 13
    F(8) = 21
    F(9) = 34
    F(10) = 55
    F(11) = 89
    F(12) = 144
    F(13) = 233
    F(14) = 377
    F(15) = 610
    F(16) = 987
    F(17) = 1597
    F(18) = 2584
    F(19) = 4181
    F(20) = 6765
    F(21) = 10946
    F(22) = 17711
    F(23) = 28657
    F(24) = 46368
    F(25) = 75025
    F(26) = 121393
    F(27) = 196418
    F(28) = 317811
    F(29) = 514229
    F(30) = 832040
    F(31) = 1346269
    F(32) = 2178309
    F(33) = 3524578
    F(34) = 5702887
    F(35) = 9227465
    F(36) = 14930352
    F(37) = 24157817
    F(38) = 39088169
    F(39) = 63245986
    F(40) = 102334155

    递归版本耗时：2965 毫秒。

    循环版本结果：
    F(1) = 1
    F(2) = 1
    F(3) = 2
    F(4) = 3
    F(5) = 5
    F(6) = 8
    F(7) = 13
    F(8) = 21
    F(9) = 34
    F(10) = 55
    F(11) = 89
    F(12) = 144
    F(13) = 233
    F(14) = 377
    F(15) = 610
    F(16) = 987
    F(17) = 1597
    F(18) = 2584
    F(19) = 4181
    F(20) = 6765
    F(21) = 10946
    F(22) = 17711
    F(23) = 28657
    F(24) = 46368
    F(25) = 75025
    F(26) = 121393
    F(27) = 196418
    F(28) = 317811
    F(29) = 514229
    F(30) = 832040
    F(31) = 1346269
    F(32) = 2178309
    F(33) = 3524578
    F(34) = 5702887
    F(35) = 9227465
    F(36) = 14930352
    F(37) = 24157817
    F(38) = 39088169
    F(39) = 63245986
    F(40) = 102334155

    循环版本耗时：45662 微秒。
    ```

    ---

