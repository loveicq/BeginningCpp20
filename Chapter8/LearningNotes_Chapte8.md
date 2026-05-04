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


