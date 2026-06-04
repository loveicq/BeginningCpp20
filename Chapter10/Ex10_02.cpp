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
{/*  */
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