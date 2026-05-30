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
    double array[]{1.5, 44.6, 13.7, 21.2, 6.7};           // C++17及以后自动推导类型为vector<double>
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