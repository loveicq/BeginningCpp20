# 第4章 决策
## 4.1 比较数据值
- 比较数据值
  - 关系运算符
  - 相等运算符
- bool值
  - true(非0值),(条件成立,真)
  - false(0),(条件不成立,假)
### 4.1.1 应用比较运算符
```cpp
#include <iostream>

int main()
{
    char first{};
    char second{};

    std::cout << "请输入一个字符:";
    std::cin >> first;
    std::cout << "请输入第二个字符:";
    std::cin >> second;

    std::cout << std::boolalpha; // 设置bool值显示为true和false,而非1和0。

    std::cout << "表达式 '" << first << " < " << second << "' 的值为"
              << (first < second) << "." << std::endl;
    std::cout << "表达式 '" << first << " == " << second << "'的值为 "
              << (first == second) << "." << std::endl;

    std::cout << std::noboolalpha; // 设置bool值显示为1和0,而非true和false。

/*
    使用下面的语句更简洁,还避免了运算符优先级的困扰:
    std::cout << std::format("表达式 '{} < {}' 的值为{}.\n", first, second, first < second);
    std::cout << std::format("表达式 '{} == {}' 的值为{}.\n", first, second, first == second);
*/
    return 0;
}
```

### 4.1.2 比较浮点数值

- NaN值既不小于、大于也不等于任何其他数字，甚至也不等于另一个NaN值
- ±Inf值，正、负无穷大

### 4.1.3 太空飞船运算符

<=>:三向比较运算符  

```cpp
#include <iostream>
#include <format>
#include <compare>

int main()
{
    std::cout << "请输入一个整数:";

    int value;
    std::cin >> value;

    std::strong_ordering ordering{value <=> 0};

    std::cout << std::format("value < 0:{}\n", ordering == std::strong_ordering::less);
    std::cout << std::format("value > 0:{}\n", ordering == std::strong_ordering::greater);
    std::cout << std::format("value == 0:{}\n", ordering == std::strong_ordering::equal);

    return 0;
}
```

1. 比较类型
    - strong_ordering（整数和指针）->less、greater、equal、equivalent
    - partial_ordering（浮点数）->less、greater、equivalent、unordered
    - weak_ordering（自定义）->less、greater、equivalent
2. 命名的比较函数（在`<compare>`中定义）
   - `std::is_lt()` 较小
   - `std::is_gt()` 较大
   - `std::is_eq()` 相等
   - `std::is_neq()` 不相等
   - `std::is_lteq()` 小于或等于
   - `std::is_gteq()` 大于或等于
## 4.2 if语句
- 简单的if语句可以写在一行上
- 0会转换为`false`，其他非0值会转换为`true`
  
```cpp
#include <iostream>

int main()
{
    std::cout << "请输入一个50-100之间的整数：";

    int value{};
    std::cin >> value;

    if (value)
    {
        std::cout << "你输入的是一个非0数字。" << std::endl;
        return 0;
    }
    if (value < 50)
        std::cout << "输入无效！你输入的数字小于50！" << std::endl;
    if (value > 100)
        std::cout << "输入无效！你输入的数字大于100！" << std::endl;

    std::cout << "你输入的数字是" << value << "。" << std::endl;

    return 0;
}
```
### 4.2.1 嵌套的if语句
```cpp
#include <iostream>

int main()
{
    std::cout << "请输入一个字母:";

    char letter{};
    std::cin >> letter;

    if (letter >= 'A')
    {
        if (letter <= 'Z')
        {
            std::cout << "你输入的是大写字母。\n";
            return 0;
        }
    }

    if (letter >= 'a') // 此处少一对花括号，也是可以的。
        if (letter <= 'z')
        {
            std::cout << "你输入的是小写字母。\n";
            return 0;
        }

    std::cout << "你输入的不是字母。\n";

    return 0;
}
```
### 4.2.2 字符分类和转换
`<cctype>`头文件提供的字符分类函数
| 函数        | 所执行的动作                                                                                                 |
| :---------- | :----------------------------------------------------------------------------------------------------------- |
| isupper(c)  | 测试c是否是大写字母                                                                                          |
| islower(c)  | 测试c是否是小写字母                                                                                          |
| isalpha(c)  | 测试c是否是大写字母或小写字母（如果区域字母表包含其他字符，那么还要测试c是否既不是大写字母，也不是小写字母） |
| isdigit(c)  | 测试c是否是数字                                                                                              |
| isxdigit(c) | 测试c是否是十六进制数字，‘0’~‘9’、‘a’~‘f’或‘A’~‘F’                                                           |
| isalnum(c)  | 测试c是否是字母或数字                                                                                        |
| isspace(c)  | 测试c是否是空白                                                                                              |
| isblank(c)  | 测试c是否是空格字符                                                                                          |
| ispunct(c)  | 测试c是否是标点符号_{}[]#()<>%:;.?*+-/^&                                                                     | ~!=,\'" |
| isprint(c)  | 测试c是否是可打印字符                                                                                        |
| iscntrl(c)  | 测试c是否是不可打印字符，即控制字符                                                                          |
| isgraph(c)  | 测试c是否是图形字符，即除了空格之外的可打印字符                                                              |

`cctype`头文件提供的字符转换函数
| 函数       | 说明                                               |
| :--------- | :------------------------------------------------- |
| tolower(c) | 如果c是大写字母，就返回该字母的小写形式，否则返回c |
| toupper(c) | 如果c是小写字母，就返回该字母的大写形式，否则返回c |

```cpp
#include <iostream>
#include <cctype>

int main()
{
    std::cout << "请输入一个字母：";

    char letter;
    std::cin >> letter;

    if (std::isupper(letter))
    {
        std::cout << "你输入的是大写字母。\n";
        return 0;
    }

    if (std::islower(letter))
    {
        std::cout << "你输入的是小写字母。\n";
        return 0;
    }

    std::cout << "你输入的不是字母。\n";

    return 0;
}
```
## 4.3 if_else语句
```cpp
// Ex4_05.cpp
// 使用if-else语句
#include <iostream>
int main()
{
    long number{};
    std::cout << "请输入一个小于20亿的整数:";
    std::cin >> number;

    if (number % 2)
    {
        std::cout << "你输入的是奇数." << std::endl;
    }
    else
    {
        std::cout << "你输入的是偶数." << std::endl;
    }
}
```
### 4.3.1 嵌套的if-else语句
else悬挂问题:if-else语句潜在造成的混淆  
- 使用花括号使代码更清晰,有时候甚至是不可或缺的
- 正确的缩进格式使代码更易读
- else总是属于前面最接近的那if
### 4.3.2 理解嵌套的if语句
```cpp
#include <iostream>

int main()
{
    char coffee{};
    char donuts{};
    char tea{};

    std::cout << "是否有咖啡?<y/n>:";
    std::cin >> coffee;

    std::cout << "是否有甜甜圈?<y/n>:";
    std::cin >> donuts;

    std::cout << "是否有茶叶?<y/n>:";
    std::cin >> tea;

    if (coffee == 'y')
    {
        if (donuts == 'y')
        {
            std::cout << "我们有咖啡和甜甜圈." << std::endl;
        }
        else
        {
            std::cout << "我们有咖啡,但是没有甜甜圈." << std::endl;
        }
    }
    else
    {
        if (tea == 'y')
        {
            std::cout << "我们没有咖啡,但是我们有茶,而甜甜圈……" << std::endl;
        }
        else
        {
            std::cout << "没有茶和咖啡，但是甜甜圈……" << std::endl;
        }
    }
}
```
## 4.4 逻辑运算符
|    运算符    |  作用  |
| :----------: | :----: |
|      &&      | 逻辑与 |
| &#124;&#124; | 逻辑或 |
|      !       | 逻辑非 |
### 4.4.1 逻辑与运算符
比较运算符的优先级高于逻辑运算符,见下面语句,'&&'运算符前后不用加小括号:  
`if(letter >= 'A' && letter <= "Z")`
### 4.4.2 逻辑或运算符
数字可以使用分隔符来增加可读性,如货币:  
一百万元:1'000'000
### 4.4.3 逻辑非运算符
```cpp
if(foo==true)
if(bar==false)
if(xyzzy!=true)
//等效于以下语句
if(foo)
if(!bar)
if(!xyzzy)
```
### 4.4.4 组合逻辑运算符
```cpp
#include <iostream>

int main()
{
    int age{};
    int income{};
    int balance{};

    std::cout << "请输入你的年龄:";
    std::cin >> age;
    std::cout << "请输入你的年收入:";
    std::cin >> income;
    std::cout << "请输入你的银行存款:";
    std::cin >> balance;

    if (age >= 21 && (income > 25'000 || balance > 100'000))
    {
        int loan{};
        if (2 * income < balance / 2)
        {
            loan = 2 * income;
        }
        else
        {
            loan = balance / 2;
        }
        std::cout << "\n你可以贷" << loan << "美元." << std::endl;
    }
    else
    {
        std::cout << "\n很抱歉,你没有贷款资格." << std::endl;
    }
}
```

👉组合逻辑运算符时,应该总是添加小括号来提高代码的清晰度：  
- (age < 30 && income > 25'000) || (age >= 30 && balance > 100'000);  
- age < 30 && income > 25'000 || age >= 30 && balance > 100'000;
### 4.4.5 对整数操作数应用逻辑运算符

if(value)  
    &nbsp;&nbsp; std::cout<<"你输入了一个非零值。"<<std::endl;  
if(!value)  
    &nbsp;&nbsp; std::cout<<"你输入了一个零值。"<<std::endl;  
if(value && value)  
    &nbsp;&nbsp; std::cout<<"两个都是非零数值。"<<std::endl;  
👉逻辑运算符的每个数值操作数首先转换为bool类型，0转换为false，其它数值转换为true。  
### 4.4.6 对比逻辑运算符与位运算符
1. 短路计算
```c++
    int x=2;

    //&&短路
    if (x < 0 && (x*x + 632*x == 1268))
    {
        std::cout << "祝贺: " << x << " 是正确的解决方案!" << std::endl;
    }

    //||短路
    if (x == 2 || (x*x + 632*2 == 1268))
    {
        std::cout << "祝贺: " << x << " 是正确的解决方案!" << std::endl;
    }
```
- &&运算符,只有第一个操作数为true时,才会计算第二个操作数
- ||运算符,只有第一个操作数为false时,才会计算第二个操作数
- &和|,两个操作数始终会被计算
2. 逻辑异或  
   `if((age < 20) ^ (balance >= 1'000'000))`
   | 按位运算符 |          说明           |                案例                |
   | :--------: | :---------------------: | :--------------------------------: |
   |   &#124;   |  只要有一个为真,即是真  | 0&#124;0=0, 1&#124;1=1, 0&#124;1=1 |
   |     &      |   只有两个为真,才是真   |        0&0=0, 1&1=1, 0&1=0         |
   |     ^      | 两个相同即为假,否则为真 |        0^0=0, 1^1=0, 0^1=1         |

## 4.5 条件运算符
条件运算符即三元运算符，通常用?:表示：条件?表达式1:表达式2
```c++
#include <iostream>
#include <format>

int main()
{
    int mice{};
    int brown{};
    int white{};

    std::cout << "How many brown mice do you have?";
    std::cin >> brown;
    std::cout << "How many white mice do you have?";
    std::cin >> white;

    mice = brown + white;

    std::cout << std::format("You have {} {} in total.\n", mice, mice == 1 ? "mouse" : "mice");
}
```
在三个选项之间进行选择：  
`std::cout<<(a < b ? "a is less than b." : 
(a == b ? "a is equal to b." : "a is greater than b."));`
## 4.6 switch语句
- 每个case值都必须是唯一的,但不必按一定的顺序
- default标签可以放到普通case标签之间的任意位置
- 如果没有default标签,且没有选中任何case值,switch语句就什么也不做
- 最后一个case(default)后面加上break语句是良好的习惯
```c++
#include <iostream>

int main()
{
    std::cout << "Your electronic recipe book is at your service.\n"
              << "You can choose from the following delicious dishes:\n"
              << "1. Boiled eggs\n"
              << "2. Fried eggs\n"
              << "3. Scrambled eggs\n"
              << "4. Coddled eggs\n\n"
              << "Enter your selection number: ";
    int choice{};
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        std::cout << "Boil some eggs." << std::endl;
        break;
    case 2:
        std::cout << "Fry some eggs." << std::endl;
        break;
    case 3:
        std::cout << "Scramble some eggs." << std::endl;
        break;
    case 4:
        std::cout << "Coddle some eggs." << std::endl;
        break;
    default:
        std::cout << "You entered a wrong number - try raw eggs." << std::endl;
        break;
    }
}
```
- 每个case值都必须是编译时常量
- 几个case值可以共享相同的操作
```c++
#include <iostream>
#include <cctype>

int main()
{
    char letter{};
    std::cout << "Enter a letter: ";
    std::cin >> letter;

    if (std::isalpha(letter))
    {
        switch (std::tolower(letter))
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            std::cout << "You entered a vowel." << std::endl;
            break;
        default:
            std::cout << "You entered a consonant." << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "You did not enter a letter." << std::endl;
    }
}
```
```c++
#include <iostream>
#include <cctype>

int main()
{
    char letter{};
    std::cout << "Enter a letter: ";
    std::cin >> letter;

    if (std::isalpha(letter))
    {
        switch (std::tolower(letter))
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            std::cout << "You entered a vowel." << std::endl;
            return 0;
        }
        std::cout << "You entered a consonant." << std::endl;
    }
    else
    {
        std::cout << "You did not enter a letter." << std::endl;
    }
}
```
**贯穿**  
- case后面没有跟break,即会贯穿到下一个case
- 大多数时候贯穿代表存在bug
- 但是贯穿并不一定总是意味着存在错误
```c++
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int ticket_number{};
    std::cin >> ticket_number;

    switch (ticket_number)
    {
    case 147:
        std::cout << "You win first prize!" << std::endl;
        break;
    case 387:
    case 123:
        std::cout << "You win second prize!" << std::endl;
        break;
    case 929:
        std::cout << "You win a special bonus prize!" << std::endl;
        [[fallthrough]]; // 此语句告诉编译器和阅读代码的人,我故意使用了贯穿行为.
    case 29:
    case 78:
        std::cout << "You win third prize!" << std::endl;
        break;
    default:
        std::cout << "Sorry, you lose!" << std::endl;
        break;
    }
}
```
## 4.7 语句块和变量作用域
```c++
//错误示例
#include <iostream>

int main()
{
    int test{3};
    switch (test)
    {
        int i{1}; // switch正常执行必须是case语句,执行不到这一句
    case 1:
        int j{2};
        std::cout << test + j << std::endl;
        break;
        int k{3}; // 已经break了,这一句也永远不会执行
    case 3:
    { // 注意,case语句后有大括号,m的作用域仅限于此大括号内,初始化是合法的
        int m{4};
        std::cout << test + m << std::endl;
        break;
    }
    default:
        int n{5};
        std::cout << test + n << std::endl;
        break;
    }
    std::cout << j << std::endl;//使用作用域外变量
    std::cout << n << std::endl;//使用作用域外变量
}
```
- 整个switch是一个作用域
- C++标准有一条重要规则:不能跳过一个带有显式初始化的变量的声明点,因switch会跳转,所以一般不能在switch语句块内定义并初始化变量,除非再用大括号包起来(创建新作用域)  

👉switch内使用新变量的解决办法
1. 使用大括号创建作用域,如:`case 1:{int x=5;...;break;}`
2. 分开声明和赋值,如:`case 1:int x;x=5;...;break;`
3. 使用复合语句,如:`case 1:if(true) {int x=5;...;}...;break;`

**初始化语句**  
👉注意!以下两个初始化语句都是在C++17以后才支持的语法
1. if (initialization; condition)...  
    `if (auto lower { static_cast <char> (std::tolower(input)) }; lower >= 'a' && lower <= 'z')`
2. switch (initialization; condition) {...}

## 4.8 本章小结
## 4.9 练习
1. 第1题
```c++
#include <iostream>

int main()
{
    int a{}, b{};

    std::cout << "输入整数a:";
    std::cin >> a;
    std::cout << "输入整数b:";
    std::cin >> b;

    if (a == b)
        std::cout << "a等于b" << std::endl;
    else
        std::cout << "a不等于b" << std::endl;
}
```
2. 第2题
```c++
#include <iostream>
#include <format>

int main()
{
    int a{}, b{};

    std::cout << "输入整数a:";
    std::cin >> a;
    std::cout << "输入整数b:";
    std::cin >> b;

    if (a <= 0 || b <= 0)
    {
        std::cout << "a和b必须是正整数!" << std::endl;
        return 1;
    }

    if (a < b)
    {
        if (b % a == 0)
            std::cout << std::format("{}是{}的整数倍.\n", b, a);
        else
            std::cout << std::format("{}不是{}的整数倍.\n", b, a);
    }
    else
    {
        if (a % b == 0)
            std::cout << std::format("{}是{}的整数倍.\n", a, b);
        else
            std::cout << std::format("{}不是{}的整数倍.\n", a, b);
    }
}
```
3. 第3题
```c++
#include <iostream>

int main()
{
    double num{};

    std::cout << "请输入一个1-100之间的数字: ";
    std::cin >> num;

    if (num < 1 || num > 100)
    {
        std::cout << "数值不在1-100范围内." << std::endl;
        return 1;
    }
    
    if (num > 50)
    {
        std::cout << "数字大于50" << std::endl;
    }
    else if (num < 50)
    {
        std::cout << "数字小于50" << std::endl;
    }
    else
    {
        std::cout << "数字等于50" << std::endl;
    }
}
```
4. 第4题
```c++
#include <iostream>
#include <cctype>

int main()
{
    // 处理年龄
    unsigned int age{};
    std::cout << "请输入你的年龄: ";
    std::cin >> age;
    if (age >= 130)
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 处理性别
    char gender{};
    std::cout << "请输入你的性别,男[m],女[f],其他[o]: ";
    std::cin >> gender;
    gender = std::tolower(gender);
    if (gender != 'f' && gender != 'm' && gender != 'o')
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 处理学历
    enum class AcademicDegree
    {
        none,
        associate,
        bachelor,
        professional,
        master,
        doctor
    };
    AcademicDegree degree;
    std::cout
        << "可能的学历:\n"
        << "\tn: 无学历\n"
        << "\ta: 副学士\n"
        << "\tb: 学士\n"
        << "\tp: 本科\n"
        << "\tm: 硕士\n"
        << "\td: 博士\n"
        << "你的最高学历是:";
    char degreeChar{};
    std::cin >> degreeChar;

    switch (degreeChar)
    {
    case 'n':
        degree = AcademicDegree::none;
        break;
    case 'a':
        degree = AcademicDegree::associate;
        break;
    case 'b':
        degree = AcademicDegree::bachelor;
        break;
    case 'p':
        degree = AcademicDegree::professional;
        break;
    case 'm':
        degree = AcademicDegree::master;
        break;
    case 'd':
        degree = AcademicDegree::doctor;
        break;
    default:
        std::cout << "你在开玩笑?\n";
        return 1;
    }

    char yes_no{};

    // 处理婚姻情况
    bool married{};
    std::cout << "你结婚了吗?已婚[y],未婚[n]: ";
    std::cin >> yes_no;
    yes_no = std::tolower(yes_no);
    if (yes_no == 'y')
        married = true;
    else if (yes_no == 'n')
        married = false;
    else
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 处理语言
    bool speaksHindi{};
    std::cout << "你会说印地语吗?会[y],不会[n]: ";
    std::cin >> yes_no;
    yes_no = std::tolower(yes_no);
    if (yes_no == 'y')
        speaksHindi = true;
    else if (yes_no == 'n')
        speaksHindi = false;
    else
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    bool speaksUrdu{};
    std::cout << "你会说乌尔都语吗?会[y],不会[n]:";
    std::cin >> yes_no;
    yes_no = std::tolower(yes_no);
    if (yes_no == 'y')
        speaksUrdu = true;
    else if (yes_no == 'n')
        speaksUrdu = false;
    else
    {
        std::cout << "你在开玩笑吗?" << std::endl;
        return 1;
    }

    // 判断是否符合要求
    if ((age > 21 && age < 35) && gender == 'f' && (degree == AcademicDegree::bachelor || degree == AcademicDegree::master) && !married && (speaksHindi || speaksUrdu))
    {
        std::cout << "恭喜你,你被录取了!" << std::endl;
    }
    else
    {
        std::cout << "对不起,你不符合我们的要求." << std::endl;
    }
}
```
5. 第5题
```c++
#include <iostream>

int main()
{
    int mice;
    int whiteMouse;
    int brownMouse;

    std::cout << "How many white mice do you have? : ";
    std::cin >> whiteMouse;
    std::cout << "How many brown mice do you have? : ";
    std::cin >> brownMouse;

    if (whiteMouse < 0 || brownMouse < 0)
    {
        std::cout << "One cannot have a negative amount of mice..." << std::endl;
        return 1;
    }

    mice = whiteMouse + brownMouse;

    std::cout << "You have " << mice << (mice == 1 || mice == 0 ? " mouse." : " mice.") << std::endl;

    if (mice == 1)
    {
        std::cout << "It is a " << (brownMouse ? "brown " : "white ") << "mouse." << std::endl;
        return 0;
    }

    if (brownMouse)
    {
        std::cout << "Of these mice, "
                  << brownMouse
                  << (brownMouse == 1 ? " is a brown" : " are brown")
                  << (brownMouse == 1 ? " mouse." : " mice.")
                  << std::endl;
    }
    else
        std::cout << "There is no brown mouse." << std::endl;
}
```
6. 第6题
```c++
#include <iostream>

int main()
{
    int num{};
    std::cout << "Input a integer: ";
    std::cin >> num;

    std::cout << "The number is "
              << (num <= 20 ? "not greater than 20." :
               (num > 20 && num <= 30 ? " greater than 20 and not greater than 30." :
                (num > 30 && num <= 100 ? " greater than 30 and not greater than 100." :
                 "greater than 100.")))
              << std::endl;
}
```
7. 第7题
```c++
#include <iostream>
#include <format>
#include <cctype>

int main()
{
    char letter{};
    std::cout << "Enter a letter: ";
    std::cin >> letter;

    // 如果字符不是字母则退出程序
    if (!std::isalpha(letter))
    {
        std::cout << "That's not a letter!" << std::endl;
        return 1;
    }

    // 判断字符是不是元音字母
    const auto lowerCaseLetter{std::tolower(letter)};
    std::cout << "'" << letter << "' is a ";
    switch (lowerCaseLetter)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        std::cout << "vowel.";
        break;
    default:
        std::cout << "consonant.";
        break;
    }
    std::cout << std::endl;

    // 判断字符是小写还是大写,并输出信息
    std::cout << "'" << letter << "' is "
              << (std::islower(letter) ? "lowercase." : "uppercase.")
              << std::endl;

    // 输出字符编码的二进制值
    std::cout << "The binary code for '" << static_cast<char>(lowerCaseLetter) << "' is 0b"
              << ((lowerCaseLetter & 0b1 << 7) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 6) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 5) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 4) ? 1 : 0)
              << "'"
              << ((lowerCaseLetter & 0b1 << 3) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 2) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 1) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 0) ? 1 : 0)
              << "."
              << std::endl;

    // 用format格式化输出二进制数值
    std::cout << "Use the format() to represent the letter in binary is " << std::format("{:#010b}.", lowerCaseLetter) << std::endl;
}
```
8. 第8题
```c++
#include <iostream>

int main()
{
    const unsigned quarter{25};
    const unsigned dime{10};
    const unsigned nickel{5};
    double amountInDollars{0.0};

    std::cout << std::endl
              << "Please enter a cash amount between 0 and 10 dollars:$";
    std::cin >> amountInDollars;

    if (amountInDollars >= 0.0 && amountInDollars <= 10.0) // 如果在0-10美元之间则执行
    {
        // 美元换算成美分
        auto amountInCents{static_cast<unsigned>(amountInDollars * 100.0 + 0.5)};

        // 计算25美分数量
        const auto quarters{amountInCents / quarter};
        amountInCents %= quarter;

        // 计算10美分数量
        const auto dimes{amountInCents / dime};
        amountInCents %= dime;

        // 计算5美分数量
        const auto nickels{amountInCents / nickel};
        const auto pennies{amountInCents % nickel};

        // 输出换算结果,并且体现单数和复数的语法
        std::cout << std::endl
                  << "The dollar value $" << amountInDollars << " can be broken down into:" << std::endl
                  << quarters << "quarter" << (quarters > 1 ? "s" : "") << "," << std::endl
                  << dimes << "dime" << (dimes > 1 ? "s" : "") << "," << std::endl
                  << nickels << "nickel" << (nickels > 1 ? "s" : "") << "," << std::endl
                  << pennies << "penn" << (pennies > 1 ? "ies" : "y") << "." << std::endl;
    }
    else
    {
        // 如果不在0-10美元之间,则提醒错误,退出程序
        std::cout << std::endl
                  << "You didn't enter an amount between $0 and $10." << std::endl;
    }
}
```