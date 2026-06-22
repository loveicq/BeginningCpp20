# 第11章 模块和名称空间

## 11.1 模块

- C++实体：变量、函数、类、枚举、模板等  
- C++中首选的机制是创建相关功能的自包含的子组件，它们被称为模块  
- 模块导出的所有实体的组合称为模块接口  
- 通常会为实现了某个公共用途的每个代码集合使用一个单独的模块

### 11.1.1 第一个模块

1. 模块命名：`module 模块名称;`，如`module math;`，如果要导出模块里面的实体，则module前面再加关键字`export`。如果module前面带有export关键字，则该文件是**模块接口文件**
2. 模块名称中允许使用点号"."，用作子模块的连接符号：`math.polynomials`
3. 在编译.cpp文件前，一般要先编译它导入的所有模块的接口文件

    ```cpp
    // Ex11_01.cpp - Consuming your own module
    import<iostream>;
    import<format>;
    import math;

    int main()
    {
        std::cout << "Lambda squared: " << square(lambda) << std::endl;

        int number;
        std::cout << "\nPlease enter an odd number: ";
        std::cin >> number;
        std::cout << std::endl;

        switch (getOddity(number))
        {
            using enum Oddity;
        case Odd:
            std::cout
                << "Well done! And remember: you have to be odd to be number one!";
            break;
        case Even:
            std::cout << std::format("Odd, {} seems to be even?", number);
            break;
        }
        std::cout << std::endl;

        std::cin.ignore();
        std::cin.get();
    }
    ```

    ```cpp
    //math.cppm - Your first module
    export module math;

    export auto square(const auto& x) { return x * x; }//An abbreviated function template

    export const double lambda{ 1.303577269034296391257 };//Conway's constant

    export enum class Oddity { Even, Odd };

    bool isOdd(int x) { return x % 2 != 0; }//Module-local function (not exported)
    export auto getOddity(int x) { return isOdd(x) ? Oddity::Odd : Oddity::Even; }
    ```

    以上程序运行结果如下：

    ---

    ```cpp
    Lambda squared: 1.69931

    Please enter an odd number: 555

    Well done! And remember: you have to be odd to be number one!
    ```

    ---

### 11.1.2 导出块

- 通过把多个实体放到一个导出块中，也可以一次性导出多个实体

    ```cpp
    //math.cppm - Exporting multiple entities at once
    export module math;

    bool isOdd(int x){return x%2 != 0;}//Module-local function (not exported)

    export
    {
        auto square(const auto& x){return x*x;}
        const module lambda{1.303577269034296391257};//Conway's constant

        enum class Oddity{Even,Odd};
        auto getOddity(int x){return isOdd(x) ? Oddity::Odd : Oddity::Even;}
    }
    ```

### 11.1.3 将接口与实现分开

- 如果在第一次声明实体时，没有使用export，那么就不能在后面声明该实体时添加export

    ```cpp
    //math.cppm - Exporting multiple entities at once
    export module math;

    export
    {
        auto square(const auto& x);
        const module lambda{1.303577269034296391257};//Conway's constant

        enum class Oddity{Even,Odd};
        auto getOddity(int x);
    }

    //The implementation of the module's function (+ local helpers)
    auto square(const auto&x){return x*x;}

    bool isOdd(int x){return x%2 != 0;}
    auto getOddity(int x){return isOdd(x) ? Oddity::Odd : Oddity::Even;}
    ```

**1. 模块实现文件**  

- 在一个模块文件中，所有import声明必须出现在module声明之后，其他任何声明之前

```cpp

```

## 11.2 名称空间

使用名称空间防止名称冲突十分重要：

- 多从开发一个应用程序时
- 应用程序包含各种第三方C++库代码时

### 11.2.1 全局名称空间

- 实体：变量、函数和类等
- 没有放在自定义的名称空间的实体就默认放在全局名称空间
- 要显式访问全局名称空间的实体，就使用"::"作用域解析运算符，注意，是不带左操作数的!

    ```cpp
    #include <iostream>

    int global_var = 10;

    int main()
    {
        int global_var = 5; // 局部变量，和全局的同名

        // 直接用，访问的是局部的 global_var
        std::cout << global_var << std::endl; // 输出：5

        // 用 :: 前缀，访问的是全局的 global_var
        std::cout << ::global_var << std::endl; // 输出：10
    }
    ```

### 11.2.2 定义名称空间

1. 名称空间定义形式如下(注意，名称空间定义的大括号后面没有分号)：

    ```cpp
    namespace mySpace{
        int var{};
        void func();
        ......
    }
    ```

2. main()函数必须放在全局名称空间中
3. 可以在不同的位置或不同的源文件中定义相同名称的名称空间，它们属于同一个名称空间
4. 通常会把名称空间的声明放在头文件（.h）中，然后在多个源文件中包含这个头文件

    ```cpp
    // Ex11_06.cpp
    // Defining and using a namespace
    #include <iostream>
    #include <numbers>

    namespace math
    {
    const double sqrt2{1.414213562373095}; // the square root of 2
    auto square(const auto &x) { return x * x; }
    auto pow4(const auto &x)
    {
        return square(square(x));
    } // 这里square就在本名称空间内，不需要"math::"限定
    } // namespace math

    int main()
    {
        std::cout << "math::sqrt2 has the value " << math::sqrt2 << std::endl;
        std::cout << "This should be 0: " << (math::sqrt2 - std::numbers::sqrt2)
                << std::endl;
        std::cout << "This should be 2: " << math::square(math::sqrt2) << std::endl;
        std::cout << "pow4(math::sqrt2) = " << math::pow4(math::sqrt2)
                << std::endl; // 这里pow4与sqrt2不在名称空间内，必须要"math::"限定
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    math::sqrt2 has the value 1.41421
    This should be 0: -2.22045e-16
    This should be 2: 2
    pow4(math::sqrt2) = 4
    ```

    ---

### 11.2.3 嵌套名称空间

两个嵌套方式：

- 直接嵌套

    ```cpp
    namespace outer
    {
        ...;
        namespace inter
        {
            ...;
        }
    }
    ```

- 简洁嵌套

    ```cpp
    namespace outer
    {
        ...;
    }

    namespace outer::inter//outer名称空间位于全局名称空间，前面不需要"::"限定。但也可以用"::"，更明确
    {
        ...;
    }
    ```

### 11.2.4 名称空间和模块

### 11.2.5 函数和名称空间

### 11.2.6 using使用指令和声明

- 使用using指令可以引用一个名称空间中的任意名称
- 声明或指令会一直应用到包含它们的块的末尾
- 应尽量少使用using指令和声明，并且尽量总是局部使用它们

### 11.2.7 名称空间别名

一般形式：`namespace alias_name = original_namespace_name;`

```cpp
namespace v2 = my_excessively_very_long_namespace_name_version2;
namespace MyGroup = MyCompany::MyModule::MySubmodule::MyGrouping;

int fancyNumber{ v2::doFancyComputation(MyGroup::queryUserInput()) };
```
