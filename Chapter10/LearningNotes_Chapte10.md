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

## 10.3 模板类型参数

Ex10_01中的larger()函数是按值接收实参，标准的机制是按引用传递实参，如下：

```cpp
template<typename T>
const T& larger(const T& a, const T& b)
{
    return a>b ? a : b;
}
```

## 10.4 显式指定模板实参

1. 编译器不能创建具有不同参数类型的模板实例，下面的程序不能编译：

    ```cpp
    std::cout<<std::format("Larger of {} and 19.6 is {}\n",small_int,larger(small_int,19.6));
    ```

2. 对于使用不同类型的实参的larger()函数，可以显式地实例化模板，将函数模板的显式类型实参放在函数名后面的尖括号中

    ```cpp
    std::cout<<std::format("Larger of {} and 19.6 is {}\n",small_int, larger<double>(samll_int,19.6));
    ```

## 10.5 函数模板的特化

1. 函数模板的特化是指为特定类型提供定制化的实现，而不是使用模板的通用逻辑
2. 特化的定义以关键字template开头，但要省略参数，所以后面的小尖括号是空的。

    ```cpp
    template<>
    int * larger(int* a,int* b)
    {
        return *a > *b ? a : b;
    }
    ```

3. 不建议使用函数模板特化。要为特定类型定制函数模板，应该使用常规函数或另一个函数模板来重载该函数模板

    ```cpp
    //重载函数模板
    template<typename T> T* larger(T* a, T* b)
    {
        return *a > *b ? a : b;
    }
    ```

## 10.6 函数模板和重载

1. 每个重载的函数都必须有唯一的签名
2. 用普通函数重载，如下：

    ```cpp
    int *larger(int* a, int* b); // Function overloading the larger template 对 larger 模板进行函数重载
    int* larger(int* a, int* b)
    {
        return *a > *b ? a : b;
    }
    ```

3. 定义另一个模板来重载原始模板，如下：

    ```cpp
    template<typename T> T* larger(T* a, T* b)
    {
        return *a > *b ? a : b;
    }
    ```

4. 注意`if(!result||value>*result)`的运算符优先级，||的短路求值，案例如下：

    ```cpp
    // Ex10_02.cpp
    // Using a function template
    #include <iostream>
    #include <string>
    #include <format>
    #include <vector>

    template <typename T>
    T larger(T a, T b);
    template <typename T>
    T *larger(T *, T *);
    template <typename T>
    const T *larger(const std::vector<T> &data);

    int main()
    {
        int big_int{17011983}, small_int{10};
        std::cout << std::format("Larger of {} and {} is {}\n",
                                big_int, small_int, larger(big_int, small_int));

        std::cout << std::format("Larger of {} and {} is {}\n",
                                big_int, small_int, *larger(&big_int, &small_int));

        std::vector<double> data{-1.4, 7.3, -100.0, 54.1, 16.3};
        std::cout << "The larger value in data is " << *larger(data) << std::endl;

        std::vector<std::string> words{"The", "higher", "the", "fewer"};
        std::cout << std::format(R"(The largest word in words is "{}")", *larger(words))
                << std::endl;
    }

    // Template for functions to return the larger of two values
    template <typename T>
    T larger(T a, T b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    T *larger(T *a, T *b)
    {
        return *a > *b ? a : b;
    }

    template <typename T>
    const T *larger(const std::vector<T> &data)
    {
        const T *result{}; // 空向量容器的最大值是nullptr
        for (const auto &value : data)
            if (!result || value > *result)
                result = &value;
        return result;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Larger of 17011983 and 10 is 17011983
    Larger of 17011983 and 10 is 17011983
    The larger value in data is 54.1
    The largest word in words is "the"
    ```

    ---

## 10.7 带多个参数的函数模板

1. 如果指定的模板实参比模板参数的数量更少，编译器将推断其他实参的类型
2. 模板定义中的参数顺序很重要。如果将返回类型作为第二参数，则总是需要指定函数调用中的两个参数。
3. 以下三行代码是等效的：
    - `std::cout<<"Larger of 1.5 and 2 is "<<larger<int>(1.5,2)<<std::endl;`
    - `std::cout<<"Larger of 1.5 and 2 is "<<larger<int,double>(1.5,2)<<std::endl;`
    - `std::cout<<"Larger of 1.5 and 2 is "<<larger<int,double,int>(1.5,2)<<std::endl;`

## 10.8 模板的返回类型推断

