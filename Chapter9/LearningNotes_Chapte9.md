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
