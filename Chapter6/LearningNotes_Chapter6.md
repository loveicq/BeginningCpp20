# 第6章 指针和引用

## 6.1 什么是指针

- 程序中每个变量和函数都位于内存的某个地方
- 指针是可存储地址的变量
  - `long* pnumber{};`//类型是"指向long"
  - 初始化列表为空,默认初始化为等价于0的指针,即不指向任何内容的地址,这种特殊的指针值写为nullptr,可显式地指定为初始值:`long* pnumber{nullptr};`
- 未初始化的指针很危险。应遵循的黄金规则:定义指针时，总是要初始化它。如果还不能为提供期望的值，就将其初始化为nullptr。
- 定义指针类型时，星号放在类型旁边或是变量名称旁边都可以
  - `long* pnumber{},number{};`//一个指针，一个普通变量
  - `long number{};long* pnumber{};`//一个指针，一个普通变量
  - `long *pnumber{},*number{};`//两个指针
- 同样的环境下，指针变量的大小是相同的：
  - 32bit:4byte
  - 64bit:8byte
```c++
#include <iostream>

int main()
{
    std::cout << sizeof(double) << " > " << sizeof(char16_t) << std::endl;
    std::cout << sizeof(double *) << " == " << sizeof(char16_t *) << std::endl;
}
```

## 6.2 地址运算符

- 地址运算符&是一元运算符，它可以获取变量的地址。
```c++ 
long number{12345L};
long* pnumber{&number};
long height{1454L};
pnumber=&height;
```
- 可以通过auto关键字，让编译器推断类型`auto pmynumber{&height};`
- 使用auto*，以便在声明中能够清晰看出这里涉及指针。`auto* mynumber{&height};`。使用auto*声明的变量只能用指针值初始化，使用其它类型的值初始化，会导致编译错误。

## 6.3 间接运算符

间接运算符可以访问指针所指向的内存位置的数据。`*pnumber`可以访问变量pnumber的数据。
```c++
#include <iostream>
#include <format>

int main()
{
    int unit_price{295};
    int count{};
    int discount_threshold{25};
    double discount{0.07};

    int *pcount{&count};
    std::cout << "Enter the number of items you want: ";
    std::cin >> *pcount;
    std::cout << std::format("The unit price is ${:.2f}\n", unit_price / 100.0);

    int *punit_price{&unit_price};
    int price{*pcount * *punit_price};
    auto *pprice{&price};

    double net_price{};
    double *pnet_price{nullptr};
    pnet_price = &net_price;
    if (*pcount > discount_threshold)
    {
        std::cout << std::format("You qualify for a discount of {:.0f} percent.\n", discount * 100);
        *pnet_price = price * (1 - discount) / 100;
    }
    else
    {
        net_price = *pprice / 100;
    }
    std::cout << std::format("The net price for {} items is ${:02f}\n", *pcount, net_price);
}
```

## 6.4 为什么使用指针

- 可以动态地为新变量分配内存空间，即在程序执行过程中分配。分配新内存时，内存由其地址标识，所以需要用指针记录它。
- 可以使用指针表示法操作存储在数组中的数据
- 指针在函数中使用非常广泛，可以在函数中访问函数外部定义的大块数据
- 指针是支持多态性起作用的基础，而多态性是面向对象编程方法提供的最重要功能。  
✴注：上面最后两项同样适用于`引用`

## 6.5 char类型的指针

- 一般在char*前面加上const关键字，避免编译异常。
```c++
#include <iostream>

int main()
{
    const char *pstar1{"Fatty Arbuckle"};
    const char *pstar2{"Clara Bow"};
    const char *pstar3{"Lassie"};
    const char *pstar4{"Slim Pickens"};
    const char *pstar5{"Boris Karloff"};
    const char *pstar6{"Mae West"};
    const char *pstar7{"Oliver Hardy"};
    const char *pstar8{"Greta Garbo"};
    const char *pstr{"Your lucky star is "};

    std::cout << "Pick a lucky star! Enter a number between 1 and 8: ";
    size_t choice{};
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        std::cout << pstr << pstar1 << std::endl;
        break;
    case 2:
        std::cout << pstr << pstar2 << std::endl;
        break;
    case 3:
        std::cout << pstr << pstar3 << std::endl;
        break;
    case 4:
        std::cout << pstr << pstar4 << std::endl;
        break;
    case 5:
        std::cout << pstr << pstar5 << std::endl;
        break;
    case 6:
        std::cout << pstr << pstar6 << std::endl;
        break;
    case 7:
        std::cout << pstr << pstar7 << std::endl;
        break;
    case 8:
        std::cout << pstr << pstar8 << std::endl;
        break;
    default:
        std::cout << "Sorry,you haven't got a lucky star." << std::endl;
    }
}
```
- 输出一个指针指向的字符串只需要指出该指针名即可。如果解引用指向字符串的指针，会只输出字符串的第一个字母（因为char*就指向第一个字母的地址）  

**指针数组**  
```c++
#include <iostream>
#include <array>

int main()
{
    const char *pstars[]{   //const不能省略,否则提示编译错误:"ISO c++禁止将字符串常量转换为‘char*’ "
        "Fatty Arbuckle",
        "Clara Bow",
        "Lassie",
        "Slim Pickens",
        "Boris Karloff",
        "Mae West",
        "Oliver Hardy",
        "Greta Garbo"};

    std::cout << "Pick a lucky star! Enter a number between 1 and "
              << std::size(pstars) << ": ";
    size_t choice{};
    std::cin >> choice;

    if (choice >= 1 && choice <= std::size(pstars))
    {
        std::cout << "Your lucky star is " << pstars[choice - 1] << "." << std::endl;
    }
    else
    {
        std::cout << "Sorry,you haven't got a lucky star." << std::endl;
    }
}
```
