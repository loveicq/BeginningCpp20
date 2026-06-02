# 第10章 函数模板

## 10.1 函数模板

1. 从函数模板中生成的函数定义称为模板的一个实例或模板的实例化
2. 函数模板的参数通常是数据类型
3. 函数模板的开头是关键字template
4. typename是一个关键字，它表示T是类型。也可以用class关键字
5. T通常用作参数名，也可以使用任何名称，如type、MY_TYPE等
6. 可以把模板放在源文件中，和普通函数定义一样。也可以为函数模板指定原型，如下：  
`template<typename T> T larger(T a, T b);//Prototype for function template 函数模板原型`

## 10.2 创建函数模板的实例

1. 编译器会从larger()函数调用的实参中推断出用于替代T的类型。这种机制称为模板实参推断
2. 编译器对每个模板实例只生成一次。即使同一个实例在不同的源文件中生成，程序也仅包含每个实例定义的一个副本

    ```cpp
    // Ex10_01.cpp
    // Using a function template
    #include <iostream>
    #include <string>
    #include <format>

    template <typename T>
    T larger(T a, T b);
    int main()
    {
        std::cout << "Larger of 1.5 and 2.5 is " << larger(1.5, 2.5) << std::endl;
        std::cout << "Larger of 3.5 and 4.5 is " << larger(3.5, 4.5) << std::endl;

        int big_int{17011983}, small_int{10};
        std::cout << std::format("Larger of {} and {} is {}\n",
                                big_int, small_int, larger(big_int, small_int));

        std::string a_string{"A"}, z_string{"Z"};
        std::cout << std::format(R"(Larger of "{}" and "{}" is "{}")",
                                // R 前缀表示 原始字符串字面量,R"(字符串内容)"格式,R = Raw（原始）
                                a_string, z_string, larger(a_string, z_string))
                << std::endl;
    }

    // Template for functions to return the larger of two values
    template <typename T>
    T larger(T a, T b)
    {
        return a > b ? a : b;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Larger of 1.5 and 2.5 is 2.5
    Larger of 3.5 and 4.5 is 4.5
    Larger of 17011983 and 10 is 17011983
    Larger of "A" and "Z" is "Z"
    ```

    ---
