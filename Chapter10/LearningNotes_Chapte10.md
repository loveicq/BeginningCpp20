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

1. 采用auto返回模板实例化类型。注意！使用auto推断返回类型，  
    函数模板定义和声明必须在一起，并且要在实例化之前定义！如下例：

    ```cpp
    // Ex10_03.cpp
    // auto自动推断返回函数模板实例化类型
    #include <iostream>
    // template <typename T1, typename T2>
    // auto larger(const T1 &a, const T2 &b);
    template <typename T1, typename T2>
    auto larger(const T1 &a, const T2 &b) // 采用auto推断必须放到函数引用的位置之前
                                        // （本例为main函数之前），不能作为函数模板声明
    {
        return a > b ? a : b; // 返回类型取决于 a > b 的结果！
    }

    int main()
    {
        int small_int{10};
        std::cout << "Larger of " << small_int << " and 9.6 is "
                << larger(small_int, 9.6) << std::endl;

        std::string a_string{"A"};
        std::cout << "Larger of \"" << a_string << "\" and \"Z\" is \""
                << larger(a_string, "Z") << '"' << std::endl;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Larger of 10 and 9.6 is 10
    Larger of "A" and "Z" is "Z"
    ```

    ---

2. `decltype(auto) // 点位符类型`
    - 使用auto或const auto&会导致返回结果的副本（复制），而不是引用&（string和向量等类型需引用），与设想不符。
    - 可以使用decltype(auto)点位符类型，此类型会计算为return语句中表达式的确切类型

    ```cpp
    // Ex10_3A.cpp
    #include <iostream>
    #include <string>
    #include <vector>

    template <typename T1, typename T2>
    decltype(auto) larger(const T1 &a, const T2 &b) {
        return a > b ? a : b;
    }

    int main() {
        const int small_int{10};
        std::cout << "Larger of " << small_int << " and 9.6 is "
                << larger(small_int, 9.6) << std::endl;

        const std::string a_string{"A"};
        std::cout << "Larger of \"" << a_string << "\" and \"Z\" is \""
                << larger(a_string, "Z") << '"' << std::endl;

        const std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        const std::vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
        std::cout << "The larger of our two vectors ends with "
                << larger(v1, v2).back() << std::endl;
        // 返回const std::vector<int>&类型
        // 向量比较大小基本与字符串比较相同：逐元素比较;遇到不等元素即停止;长度决定
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Larger of 10 and 9.6 is 10
    Larger of "A" and "Z" is "Z"
    The larger of our two vectors ends with 11
    ```

    ---

3. 注意！只应该在模板中能使用decltype(auto)。在非通用代码中，总是应该显式选择使用更具体的auto或(const)auto。

## 10.9 模板参数的默认值

1. 可以为模板参数指定默认值，如下：

    ```cpp
    //Template with default value for the first parameter
    template<typename RreturnType=double,typename T1,typename T2>
    ReturnType larger(const T1&,const T2&); 
    ```

2. 指定模板参数的默认值不一定是好主意
3. 模板参数默认值与普通函数参数默认值要求不一样，模板参数默认值可以放在前、中、后参数。 但是，在参数列表末尾指定模板实参的默认值仍是常见的做法。

## 10.10 非类型的模板参数

1. 一个案例：  

    ```cpp
    // Text10_01.cpp
    // 非类型的模板参数
    #include <iostream>

    template <typename T, int lower, int upper>
    bool is_in_range(const T& value) {
        return value >= lower && value <= upper;
    }

    int main() {
        double value{200.0};
        // std::cout<<is_in_range(value)<<std::endl;//无法编译，因为少了参数
        std::cout << is_in_range<double, 0, 100>(value) << std::endl;  // OK!
        //<double, 0,
        //100>是模板参数列表，必须是编译期常量，(value)是函数参数列表，可以运行时提供

        // int i{5};//不是常量，不能编译
        const int i{5};//有const，是常量，可以编译
        std::cout << is_in_range<double, i, i * 100>(value) << std::endl;
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    0
    1
    ```

    ---

2. 最佳的做法是将类型参数T置于最后（这样可以推断出该类型），并为lower和upper使用auto（为了避免硬编码其类型）

    ```cpp
    // Test10_02.cpp
    // 非类型模板参数的最佳做法
    #include <iostream>

    template <auto lower, auto upper, typename T>
    bool is_in_range(const T& value) {
        return value >= lower && value <= upper;
    }

    int main() {
        double value{100.0};
        std::cout << is_in_range<0, 50>(value)
                << std::endl;  // 类型T可以通过value推断出来
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    0
    ```

    ---

**使用固定大小数组实参的函数模板**  

```cpp
// Ex10_04.cpp
// 使用固定大小的数组实参的函数模板
#include <iostream>

template <typename T, size_t N> T average(const T (&array)[N]);

int main()
{
double doubles[2]{1.0, 2.0};
std::cout << average(doubles) << std::endl;

double moreDoubles[]{1.0, 2.0, 3.0, 4.0};
std::cout << average(moreDoubles) << std::endl;

std::cout << average({1.0, 2.0, 3.0, 4.0}) << std::endl; // 有大括号

int ints[]{1, 2, 3, 4};
std::cout << average(ints) << std::endl;
}

template <typename T, size_t N> T average(const T (&array)[N])
{
T sum{};
for (size_t i{}; i < N; ++i)
    sum += array[i];
return sum / N;
}
```

上面程序运行结果如下：

---

```cpp
1.5
2.5
2.5
2
```

---