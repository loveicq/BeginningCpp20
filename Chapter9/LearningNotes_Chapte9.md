# 第9章 词汇类型

## 9.1 使用可选值

**std::optional**模板类，`std::optional<T>` 函数返回std::optional类对象（变量）

```cpp
// Ex9_01.cpp
// Working with std::optional<>
#include <iostream>
#include <string>
#include <optional> //std::optional<> is defined in the <optional> module

std::optional<size_t> find_last(
    const std::string &string, char to_find,
    std::optional<size_t> start_index = std::nullopt); // or: ... start_index = {});

int main()
{
    const auto string = "Growing old is mandatory; growing up is optional.";

    const std::optional<size_t> found_a{find_last(string, 'a')};
    if (found_a)
        std::cout << "Found the last a at index " << *found_a << std::endl;

    const auto found_b{find_last(string, 'b')};
    if (found_b.has_value())
        std::cout << "Found the last b at index " << found_b.value() << std::endl;

    // following line gives an error (cannot convert std::optional<size_t> to size_t)
    // const size_t found_c{ find_last(string,'c')};
    const auto found_early_i{find_last(string, 'i', 10)};
    if (found_early_i != std::nullopt)
        std::cout << "Found an early i at index " << *found_early_i << std::endl;
}

std::optional<size_t> find_last(const std::string &string, char to_find,
                                std::optional<size_t> start_index)
{
    // code below will not work for empty strings
    if (string.empty())
        return std::nullopt; // or: 'return std::optional<size_t>{};'
                             // or: 'return {};'
    // determine the starting index for the loop that follows:
    size_t index = start_index.value_or(string.size() - 1);

    while (true) // never use while (index >= 0) here, as size_t is always >= 0!
    {
        if (string[index] == to_find)
            return index;
        if (index == 0)
            return std::nullopt;
        --index;
    }
}
```

注意：

1. std::optional对象有三个成员函数
   - .has_value() 检查是否有值
   - .value() 取值
   - .value_or() 取值，如果为空就返回默认值
2. *found_a 也是取std::optional对象的值，前提是得有值，否则会出错！

以上示例程序运行结果如下：

---

```cpp
Found the last a at index 46
Found an early i at index 4
```

---

## 9.2 字符串视图：新的const string引用

1. 三种字符串存储方式的区别
    - std::string 对象：`std::string str = "hello";`
    - 字符串字面量：`const char* literal = "hello";  // 或直接使用 "hello"`
    - C风格字符串（字符数组）：`char c_str[] = "hello";`
2. string_view 如何统一处理这三种字符串

    ```cpp
    // 三种不同存储方式的字符串
    std::string str = "hello";           // 堆上
    const char* literal = "world";       // 只读数据段
    char c_array[] = "test";             // 栈上

    // string_view 可以统一观察它们，无需复制
    std::string_view sv1 = str;          // OK
    std::string_view sv2 = literal;      // OK  
    std::string_view sv3 = c_array;      // OK

    // 甚至可以观察部分字符串
    std::string_view sv4 = str.substr(1, 3);  // 观察 "ell"
    ```

3. 关键要点
    - string_view 不复制任何字符数据
    - 它只保存指向原始数据的指针和长度
    - 必须保证原始数据的生命周期长于 string_view

    ```cpp
    std::string_view bad() {
        std::string temp = "hello";  // 局部变量
        return std::string_view(temp);  // 返回后 temp 销毁，sv 悬空！这是最常见的陷阱！
    }
    ```

### 9.2.1 使用字符串视图函数参数

1. 编译器会拒绝将std::string_view对象隐式转换为std::string类型的值。  
但书中的示例可以用`words.emplace_back(text.substr(start,end-start));`来避免显式转换。
2. std::string_view没有提供c_str()函数，将它转换为一个const char*数组，但它提供了data()函数
3. 不能使用加法运算符(+)来连接std::string_view，必须先转换为std::string才能使用‘+’连接符

    ```cpp
    // Ex9_02.cpp
    // Using std::string_view parameters
    #include <iostream>
    #include <string>
    #include <vector>
    #include <string_view>
    #include <format>

    void find_words(std::vector<std::string> &words,
                    std::string_view text,
                    std::string_view separators, size_t &maxStr);
    void list_words(const std::vector<std::string> &words,
                    const size_t maxStr);

    int main()
    {
        std::string text;
        std::cout << "请输入字符串，以*号结束：\n";
        std::getline(std::cin, text, '*');

        const std::string separators{" ,;:.\"!?'\n"};
        std::vector<std::string> words;
        size_t maxStr{}; // 最大的单词字符数
        find_words(words, text, separators, maxStr);
        list_words(words, maxStr);
    }

    void find_words(std::vector<std::string> &words,
                    std::string_view text,
                    std::string_view separators, size_t &maxStr)
    {
        size_t start{text.find_first_not_of(separators)};

        while (start != std::string_view::npos)
        {
            size_t end{text.find_first_of(separators, start + 1)};
            if (end == std::string_view::npos)
                end = text.length();
            words.emplace_back(text.substr(start, end - start));
            if (maxStr < end - start)
                maxStr = end - start;
            start = text.find_first_not_of(separators, end + 1);
        }
    }

    void list_words(const std::vector<std::string> &words,
                    const size_t maxStr)
    {
        if (words.empty())
        {
            std::cout << "你未输入字符串，程序即将退出。" << std::endl;
            return;
        }

        size_t count{};
        for (const auto &word : words)
        {
            std::cout << std::format("{:<{}}", word, maxStr + 1);
            if (++count % 5 == 0)
                std::cout << std::endl;
        }

        std::cout << std::endl;
    }
    ```

    上面示例程序运行结果如下：

    ---

    ```cpp
    请输入字符串，以*号结束：
    The morning sun filtered through the kitchen window, casting warm golden rays on the wooden table. A fresh pot of coffee steamed gently, its rich aroma mixing with the scent of freshly baked bread. Outside, birds chirped happily in the oak tree, while a soft breeze rustled the leaves. I sipped my coffee slowly, enjoying the peaceful moment before the day's busy schedule began.*

    字符串分解单词列举如下：
    The      morning  sun      filtered through  
    the      kitchen  window   casting  warm     
    golden   rays     on       the      wooden   
    table    A        fresh    pot      of       
    coffee   steamed  gently   its      rich     
    aroma    mixing   with     the      scent    
    of       freshly  baked    bread    Outside  
    birds    chirped  happily  in       the      
    oak      tree     while    a        soft     
    breeze   rustled  the      leaves   I        
    sipped   my       coffee   slowly   enjoying 
    the      peaceful moment   before   the      
    day      s        busy     schedule began
    ```

    ---

### 9.2.2 合适的动机

如果char数组不是空字符元素终止，就不能构造string_view对象，  
要用`std::string_view{text,numCharacters}`这种[指针+长度]的格式直接构造string_view对象

## 9.3 span：新的向量或数组引用

1. 一个类型的连续序列，可以用std::span<>对象来替代（C++20及以后）
2. std::span<>对象提供范围支持和方括号操作符
3. std::span<>对象提供size()、empty()、data()、front()和back()等函数

    ```cpp
    //Ex9_03.cpp
    // 使用 std::span<> 减少 largest() 函数的重载数量
    // 显然，这三个生成的函数仍然很相似。
    // 有关如何使用函数模板消除这种重复代码，请参见第10章。
    #include <iostream>
    #include <string>
    #include <vector>
    #include <array>
    #include <span>

    // 旧的函数原型
    // double largest(const double data[], size_t count);
    // double largest(const std::vector<double>& data);
    // int largest(const std::vector<int>& data);
    // std::string largest(const std::vector<std::string>& words);

    // 新的函数原型
    // （这些函数适用于任何连续输入，不仅限于数组或向量）
    /* 注意：这些签名还不是理想的：请参见 Ex9_03A */
    double largest(std::span<const double> data);
    int largest(std::span<const int> data);
    std::string largest(std::span<const std::string> words);

    int main()
    {
        double array[]{1.5, 44.6, 13.7, 21.2, 6.7};
        std::vector numbers{15, 44, 13, 21, 6, 8, 5, 2};      // C++17及以后自动推导类型为vector<int>
        std::vector data{3.5, 5.0, 6.0, -1.2, 8.7, 6.4};      // C++17及以后自动推导类型为vector<double>
        std::array array_data{3.5, 5.0, 6.0, -1.2, 8.7, 6.4}; // 顺便加入一个 std::array 作为补充测试;
                                                              // C++17及以后自动推导类型为array<double,6>
        std::vector<std::string> names{"Charles Dickens", "Emily Bronte",
                                    "Jane Austen", "Henry James", "Arthur Miller"};
        std::cout << "The largest of array is " << largest(array) << std::endl;
        std::cout << "The largest of numbers is " << largest(numbers) << std::endl;
        std::cout << "The largest of data is " << largest(data) << std::endl;
        std::cout << "The largest of array_data is (also) " << largest(array_data) << std::endl;
        std::cout << "The largest of names is " << largest(names) << std::endl;
    }

    // 在 span 中查找最大值
    double largest(std::span<const double> data)
    {
        double max{data[0]};
        for (auto value : data)
            if (max < value)
                max = value;
        return max;
    }

    // 在 int 类型的向量中查找最大值
    int largest(std::span<const int> data)
    {
        int max{data[0]};
        for (auto value : data)
            if (max < value)
                max = value;
        return max;
    }

    // 在 string 对象的向量中查找最大值
    std::string largest(std::span<const std::string> words)
    {
        std::string max_word{words[0]};
        for (const auto &word : words)
            if (max_word < word)
                max_word = word;
        return max_word;
    }
    ```

    以上程序运行结果如下：

    ---

    ```cpp
    The largest of array is 44.6
    The largest of numbers is 44
    The largest of data is 8.7
    The largest of array_data is (also) 8.7
    The largest of names is Jane Austen
    ```

    ---

### 9.3.1 span与视图

1. std::span<>与std::string_view一样，都不会复制底层数组的元素
2. 与std::string_view不同，std::span<>允许对底层数组的元素进行重新赋值或修改
3. std::span<>不能增加或删除任何元素
4. `std::span<double> my_span(my_vector);`是从容器构造初始化，也可以写作  
`std::span<double> my_span{my_vector};`，更现代化。

### 9.3.2 const元素的span

1. 用`span<const T>`替代`const vector<T>&`
2. 用`span<T>`替代`vector<T>&`，除非需要插入或删除元素

### 9.3.3 固定大小的span

1. 使用`span<T,N>`替代`array<T,N>&`或`T(&)[N]`
2. 使用`span<const T,N>`替代`const array<T,N>&`或`const T(&)[N]`
3. 体会以下三个函数的差别  
    `double average10(std::span<const double,10>values)`  
    `double average10(const double (&values)[10]);`  
    `double average10(const std::array& values);`  

    ```cpp
    // Ex9_04.cpp
    // 使用span<T,N>替代T(&)[N]
    #include <iostream>

    double average10(std::span<double, 10> values);

    int main()
    {
        double values[]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
        std::cout << "Average = " << average10(values) << std::endl;
    }

    double average10(std::span<double, 10> values)
    {
        double sum{};
        for (auto value : values)
            sum += value;
        return sum / 10;
    }
    ```

    上面示例程序运行结果如下：

    ---

    ```cpp
    Average = 5.5
    ```

    ---

## 9.4 本章小结

## 9.5 练习

1. 第1题

    ```cpp
    /*************************第9章_练习_第1题************************
    修改Ex9_01，在其中使用std::string_view。
    *****************************************************************/
    #include <iostream>
    #include <optional>
    #include <string_view>

    std::optional<size_t> find_last(std::string_view string,
                                    char to_find,
                                    std::optional<size_t> start_index = std::nullopt);

    int main()
    {
        const auto string{"Growing old is mandatory; growing up is optional."};
        // 此处可以用列表初始化，不用‘=’号了，因为std::string_view已经包含size()等属性

        const std::optional<size_t> found_a{find_last(string, 'a')};
        if (found_a)
            std::cout << "Found the last a at index " << *found_a << std::endl;

        const auto found_b{find_last(string, 'b')};
        if (found_b.has_value())
            std::cout << "Found the last b at index " << found_b.value() << std::endl;

        const auto found_early_i{find_last(string, 'i', 10)};
        if (found_early_i != std::nullopt) // 此句有没有"!= std::nullopt"效果都是一样的
            std::cout << "Found an early i at index " << *found_early_i << std::endl;
    }

    std::optional<size_t> find_last(std::string_view string,
                                    char to_find,
                                    std::optional<size_t> start_index)
    {
        if (string.empty())
            return std::nullopt;

        size_t index = start_index.value_or(string.size() - 1);
        while (true)
        {
            if (string[index] == to_find)
                return index;
            if (index == 0)
                return std::nullopt;
            --index;
        }
    }
    ```

    以上程序运行效果如下：

    ---

    ```cpp
    Found the last a at index 46
    Found an early i at index 4
    ```

    ---

2. 第2题

    ```cpp
    /*************************第9章_练习_第2题************************
    修改Ex8_11，在其中使用std::string_view和std::span<>。
    *****************************************************************/
    #include <iostream>
    #include <string_view>
    #include <span>
    #include <format>

    void show_data(std::span<int> data,
                std::string_view title = "Data Values",
                size_t width = 10, size_t perline = 5);

    int main()
    {
        int samples[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

        int dataItem{-99};
        show_data(std::span{&dataItem, 1});

        dataItem = 13;
        show_data(std::span{&dataItem, 1}, "Unlucky for some!");

        show_data(samples);
        show_data(samples, "Samples");
        show_data(samples, "Samples", 6);
        show_data(samples, "Samples", 8, 4);
    }

    void show_data(std::span<int> data,
                std::string_view title,
                size_t width, size_t perline)
    {
        std::cout << title << std::endl;
        size_t size{};
        for (auto value : data)
        {
            std::cout << std::format("{:{}}", value, width);
            if (++size % perline == 0)
                std::cout << '\n';
        }
        std::cout << std::endl;
    }
    ```

    以上程序运行结果如下：

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

3. 第3题

    ```cpp
    /*************************第9章_练习_第3题************************
    修改Ex8_13，在其中使用词汇类型。
    *****************************************************************/
    #include <iostream>
    #include <format>
    #include <span>
    #include <string_view>
    #include <optional>

    void show_data(std::span<const double> data,
                std::string_view title = "Data Values",
                size_t width = 10, size_t perLine = 5);
    std::optional<double> largest(std::span<const double> data);
    std::optional<double> smallest(std::span<const double> data);
    std::span<double> shift_range(std::span<double> data, double delta);
    std::span<double> scale_range(std::span<double> data, double divisor);
    std::span<double> normalize_range(std::span<double> data);

    int main()
    {
        double samples[]{
            11.0, 23.0, 13.0, 4.0,
            57.0, 36.0, 317.0, 88.0,
            9.0, 100.0, 121.0, 12.0};
        show_data(samples, "Original Values");       // Output original values
        normalize_range(samples);                    // Normalize the values
        show_data(samples, "Normalized Values", 12); // Output normalized values
    }

    // Output an array of double values
    void show_data(std::span<const double> data,
                std::string_view title, size_t width, size_t perLine)
    {
        std::cout << title << std::endl; // Display the title
        // Output the data value
        size_t count{};
        for (auto currentValue : data)
        {
            std::cout << std::format("{:{}.6g}", currentValue, width);
            if (++count % perLine == 0)
                std::cout << '\n';
        }
        std::cout << std::endl;
    }

    std::optional<double> smallest(std::span<const double> data)
    {
        if (data.empty())
            return std::nullopt; // There is no smallest in an empty array

        double minValue{data[0]};
        for (auto currentValue : data)
            if (minValue > currentValue)
                minValue = currentValue;
        return minValue;
    }

    std::span<double> shift_range(std::span<double> data, double delta)
    {
        for (auto &currentValue : data) // 注意！必须是&引用才能改变数据，否则是值拷贝，不能改变数据
            currentValue += delta;
        return data;
    }

    std::optional<double> largest(std::span<double> data)
    {
        if (data.empty())
            return std::nullopt; // There is no largest in an empty array

        double maxValue{data[0]};
        for (auto currentValue : data)
            if (maxValue < currentValue)
                maxValue = currentValue;

        return maxValue;
    }

    std::span<double> scale_range(std::span<double> data, double divisor)
    {
        if (!divisor)
            return data; // Do nothing for a zero divisor

        for (auto &currentValue : data)
            currentValue /= divisor;
        return data;
    }

    std::span<double> normalize_range(std::span<double> data)
    {
        if (data.empty()) // 空数据直接返回，防止后面*解引用出错
            return data;

        //此题教材答案有bug
        // 先取出最小和最大值，因为shift_range()函数会改变原数据
        // 后面scale_range()的参数得到的是修改后的数据
        auto minValue = smallest(data);
        auto maxValue = largest(data);

        shift_range(data, -*minValue); // std::optional的值需要*取出
        return scale_range(data, *maxValue);
    }
    ```

    上面程序运行结果如下：

    ---

    ```cpp
    Original Values
        11        23        13         4        57
        36       317        88         9       100
       121        12
    Normalized Values
        0.022082   0.0599369   0.0283912           0    0.167192
        0.100946    0.987382    0.264984   0.0157729    0.302839
        0.369085   0.0252366
    ```

    ---
