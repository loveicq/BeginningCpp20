# 第11章 模块和名称空间

## 11.1 模块

- C++实体：变量、函数、类、枚举、模板等  
- C++中首选的机制是创建相关功能的自包含的子组件，它们被称为模块  
- 模块导出的所有实体的组合称为模块接口  
- 通常会为实现了某个公共用途的每个代码集合使用一个单独的模块

### 11.1.1 第一个模块



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
