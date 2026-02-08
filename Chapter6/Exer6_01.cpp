// Exer6_01.cpp
#include <iostream>
#include <format>
#include <array>

int main()
{
    const unsigned NUMBER{50};     // 要输出的奇数数量
    unsigned oddNumbers[NUMBER]{}; // 只考虑正奇数

    // 生成正奇数
    for (size_t i{}; i < NUMBER; ++i)
        oddNumbers[i] = 2 * i + 1;

    // 计算数组最后一个元素的位数
    unsigned maxValue{oddNumbers[NUMBER - 1]};
    size_t count{std::to_string(maxValue).length()};
    size_t width{count + 1};

    // 用指针正序输出数组元素（数组名退化为指针），每行10个元素
    std::cout << "正序输出：" << std::endl;
    for (size_t i{}; i < NUMBER; ++i)
    {
        std::cout << std::format("{:{}}", *(oddNumbers + i), width); // 输出数字和宽度
        if ((i + 1) % 10 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;

    // 用指针逆序输出数组元素（数组名退化为指针），每行10个元素
    std::cout << "逆序输出：" << std::endl;
    const auto *pOddNumbersFinal{oddNumbers + NUMBER - 1};
    for (size_t i{}; i < NUMBER; ++i, --pOddNumbersFinal)
    {
        std::cout << std::format("{:{}}", *pOddNumbersFinal, width);
        if ((i + 1) % 10 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}