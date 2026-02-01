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
## 6.6 常量指针和指向常量的指针
1. 指向常量的指针。指针指向的内容不能修改，但可以把指针设置为指向其他内容。
    - `const char* pstring{"Some text that cannot be changed"};`
    - `const int value{20};`,`const int* pvalue{&value};`
    - 不能在非const类型的指针中存储const类型变量的地址
2. 常量指针。存储在指针中的地址不能修改。常量指针只能指向初始化时指定的地址，但是地址的内容不是常量，可以修改。
    - `int data{20};`,`int* const pdata{&data};`,`*pdata=25;`//允许修改
    - 如果data声明为常量，就不能用&data初始化pdata，指针pdata只能指向int类型的非const变量。
3. 指向常量的常量指针。存储在指针中的地址和指针指向的内容都是常量，都不能修改。
    - `const float value{3.1415f};`,`const float* const pvalue{&value`  

💯 **C++ const 修饰符完整指南**

1. 基本类型等价性

   1.1 const float = float const（完全等价）  
   1.2 当 const 修饰非指针、非引用的基础类型或类类型时，它可以放在类型说明符的前面或后面，效果相同
    ```cpp
    const int a = 5;     // 正确
    int const b = 5;     // 正确，与上一行完全等价
    const MyClass obj1;  // 正确
    MyClass const obj2;  // 正确，与上一行完全等价
    ```

2. 指针声明中的 const 位置规则  

    2.1 const 在 * 左边 → 修饰指向的数据
    ```cpp
    const int * p1;        // 指向 const int 的指针（数据不可变）
    int const * p2;        // 同上，完全等价

    // 特性：指针可以重新赋值，但不能通过指针修改数据
    int x = 10, y = 20;
    const int * p = &x;
    p = &y;                // 正确：指针可以指向其他地址
    // *p = 30;            // 错误：不能通过指针修改数据
    ```
    2.2 const 在 * 右边 → 修饰指针本身  
    ```cpp
    int * const p3 = &x;   // 指向 int 的 const 指针（指针不可变）

    // 特性：指针一旦初始化就不能改变，但可以通过指针修改数据
    int x = 10, y = 20;
    int * const p = &x;
    *p = 30;              // 正确：可以修改指向的数据
    // p = &y;            // 错误：指针本身不能改变
    ```
    2.3 两边都有 const → 双重保护  
    ```cpp
    const int * const p4 = &x;    // 指向 const int 的 const 指针
    int const * const p5 = &x;    // 同上，完全等价

    // 特性：指针不能改变，也不能通过指针修改数据
    int x = 10;
    const int * const p = &x;
    // *p = 20;           // 错误：不能修改数据
    // p = nullptr;       // 错误：不能修改指针
    ```

3. 解读复杂声明的正确方法（从右向左读规则）  

    3.1 基本步骤
      - 找到标识符（变量名）
      - 向右看 → 检查是否有 []（数组）或 ()（函数）
      - 向左看 → 遇到 *（指针）或 &（引用）
      - 继续向左 → 确定最终类型  

    3.2 示例分析
    ```cpp
    float const * const pvalue{&value};
    ```
    **分析步骤：**
    ```text
    步骤1: 找到标识符 → pvalue
    步骤2: 向右看 → 没有 [] 或 ()
    步骤3: 向左看 → 遇到 const，它修饰什么？
    * const pvalue → 表示 pvalue 是一个常量指针
    步骤4: 继续向左 → float const → 表示指向的类型是常量 float
    ✅最终: pvalue 是一个常量指针，指向常量 float
    ```
    3.3 更复杂的例子  
    ```cpp
    // 示例1：指针数组
    const int * arr[10];        // arr 是数组[10]，元素是指向 const int 的指针

    // 示例2：指向数组的指针
    int (*ptr)[10];             // ptr 是指针，指向数组[10] of int

    // 示例3：指向函数的指针
    void (*funcPtr)(int);       // funcPtr 是指针，指向函数（参数int，返回void）
    ```

4. 理解技巧与记忆方法

    4.1 分解写法  
    将复杂声明分解为两部分：
    ```cpp
    float const * const pvalue;
    // 可以看作：
    // (float const)   (* const pvalue)
    // ↑指向的类型     ↑指针声明部分
    ```
    4.2 英语读法  
    - `int * p;` → "p is a pointer to int"
    - `const int * p;` → "p is a pointer to const int"
    - `int * const p = &x;` → "p is a const pointer to int"
    - `const int * const p = &x;` → "p is a const pointer to const int"  

    4.3 视觉对齐技巧
    ```cpp
    const int  *       p1;    // p1 是指针，指向 const int
    int       * const  p2;    // p2 是 const 指针，指向 int
    const int * const  p3;    // p3 是 const 指针，指向 const int
    ```

5. 重要注意事项

    5.1 初始化要求
    ```cpp
    int * a{};           // 正确：值初始化为 nullptr
    int * const b{};     // 错误：const 指针必须显式初始化
    int * const c = &x;  // 正确：必须立即初始化
    const int * d;       // 正确：可以稍后赋值（指针本身不是const）
    ```
    5.2 类型等价性验证
    ```cpp
    #include <type_traits>

    static_assert(std::is_same_v<const int, int const>);          // 通过
    static_assert(std::is_same_v<const int*, int const*>);        // 通过
    static_assert(std::is_same_v<int* const, int* const>);        // 通过
    static_assert(std::is_same_v<const int* const, int const* const>); // 通过
    ```
    5.3 常见错误
    ```cpp
    // 错误1：const 位置错误
    int * a const;       // 错误：const 不能放在标识符后面（成员函数除外）

    // 错误2：忘记初始化 const 指针
    int * const ptr;     // 错误：const 指针必须初始化

    // 错误3：误解 const 位置
    int const * p;       // 正确：指向 const int 的指针
    // 很多人误以为这是 const 指针，其实不是！
    ```

6. 实战练习

    测试你的理解：
    ```cpp
    int x = 10;
    const int y = 20;

    // 以下哪些是正确的？
    const int * p1 = &x;        // ✓
    int * const p2 = &x;        // ✓
    const int * const p3 = &x;  // ✓
    int * p4 = &y;              // ✗
    const int * p5 = &y;        // ✓
    ```

7. 总结表格  

| 声明格式              | 指针本身 | 指向的数据 | 读法                         |
| :-------------------- | :------- | :--------- | :--------------------------- |
| `int * p`             | 可变     | 可变       | 指向 int 的指针              |
| `const int * p`       | 可变     | 不可变     | 指向 const int 的指针        |
| `int const * p`       | 可变     | 不可变     | 同上                         |
| `int * const p`       | 不可变   | 可变       | 指向 int 的 const 指针       |
| `const int * const p` | 不可变   | 不可变     | 指向 const int 的 const 指针 |

✅记住黄金法则：从右向左读，const 修饰它左边紧邻的东西（在指针声明中）。  

## 6.7 指针和数组

1. 数组名会退化为指针，除了char类型的数组(因为所有标准输出流都假定它是C样式的字符串)。因为数组名可以解释为地址，所以也可以用于初始化指针。
```cpp
double values[10];
double* pvalue{value};
```
2. 尽管数组名是一个地址，但它不是指针。存储在指针中的地址可以修改，而数组名表示的地址是固定的。

### 6.7.1 指针的自述运算

1. 指针可以进行加减，得到地址结果；也可以进行指针比较，得到逻辑结果。
```cpp
double values[10];
double* pvalue{value};   //pvalue=value[0]的地址
++pvalue;                //自增后，pvalue=value[1]的地址，或pvalue += 1
```
2. 数组指针不一定指向数组的开始地址。
```cpp
double values[10];
double* pvalue{&value[3]};   //pvalue=value[3]的地址
//也可以用数组名偏移的方式得到地址，如：double* pvalue{value+3};
++pvalue;                    //自增后，pvalue=value[4]的地址
```
3. 表达式pvalue + n的结果是给指针pvalue指向的地址加上n*sizeof(double)。
```cpp
*(pvalue + 1) = *(pvalue+2);
value[4]=value[5];  //与上式等价
```
4. pvalue+1不会改变pvalue中的地址，而++pvalue和pvalue+=n会改变pvalue中的地址。
5. 在递增或递减指针包含的地址后，解引用要使用小括号。
```cpp
//假设pvalue指向value[3]
*(pvalue+1);    //解引用，得到value[4]的值
*pvalue+1;      //先解引用得到value[3]的值，再+1
```
6. 如果指针包含无效的地址（如在它指向的数组上下限之外的地址），使用该指针存储一个值时，就会改写该地址所在的内存。这一般会导致灾难，程序将以某种方式失败。

**1.计算两个指针之间的差**  

1. 可以从一个指针减去另一个指针，但这仅在指针的类型相同且指向同一个数组中的元素时才有意义。
```cpp
long numbers[]{10,20,30,40,50,60,70,80};
long* pnum1{&number[6]};//Point to 7th array element
long* pnum2{&number[1]};//Point to 2nd array element
auto difference {pnum1-pnum2};//Result is 5
auto difference2 {pnum2-pnum1};//Result is -5
```
指针之差由元素（而不是由字节）决定。  

2. C++语言规定，将两个指针相减，得到的值的类型为std::ptrdiff_t，这是在<csddef>模块中定义的某个带符号的整形的平台特定的类型`别名`
```cpp
std::ptrdiff_t difference2 {pnum2-pnum1};//Result is -5
```
取决于平台，std::ptrdiff_t通常是int、long或long long的别名。

**2.比较指针**


使用==、!=、<、>、<=和>=运算符，可以安全地比较相同类型的指针。如果指针指向的数组位置更深，或者所指向的元素的索引更高，指针就更大。
```cpp
pnum2<pnum1;//结果为true，因为pnum2-pnum1<0
```

### 6.7.2 使用数组名的指针表示法

```cpp
long data[5]{};
//把data数组的值设置为偶数
for(size_t i{};i<std::size(data);++i)
    *(data+i)=2*(i+1);
//累加数组元素的值
long sum{};
for(size_t i{};i<std::size(data);++i)
    sum+=*(data+i);
```
```cpp
//Ex6_05.cpp
//利用指针计算质数
#include <iostream>
#include <format>

int main()
{
    const size_t max{100};
    long primes[max]{2L};
    size_t count{1};
    long trial{3L};
    while (count < max)
    {
        bool isprime{true};
        for (size_t i{}; i < count && isprime; ++i)
        {
            isprime = trial % *(primes + i) > 0;
        }

        if (isprime)
        {
            *(primes + count++) = trial;
        }
        trial += 2;
    }

    std::cout << "The first " << max << " primes are:" << std::endl;
    for (size_t i{}; i < max; ++i)
    {
        std::cout << std::format("{:7}", *(primes + i));
        if ((i + 1) % 10 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}
```
**案例理解**  
1. 质数是指在大于1的自然数中，除了1和它本身以外不再有其他因数的数。
2. 2是最小的偶质数，3是最小的奇质数。
3. 数组primes赋一个初值2，因为2是已知最小质数，同时不全部初始化为0，也避免了后面trial % *(primes+i)可能会产生被除数为0的错误。
4. count赋初值为1，是因为已知第一个元素primes[0]=2，而如果count为0的话，*(primes + count++) 就不对了。
5. trial赋初值为3，是因为下面从3开始测试。
6. trial+=2;是避免计算偶数，因为偶数都不是质数（2除外）。
7. 整个程序写得很紧凑，主要注意数组名退化为指针的用法：`*(primes+i)`和`*(primes+count)`。