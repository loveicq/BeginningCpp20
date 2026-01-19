#include <iostream>
#include <vector>
#include <format>

int main()
{
    unsigned maxInteger{};
    std::cout << "Enter a non-negative integer: ";
    std::cin >> maxInteger;

    std::vector<int> integers;
    integers.reserve(maxInteger); // 预先一次分配合适的内存,避免每次push_back()都重新分配内存

    for (size_t i{}; i < maxInteger; ++i)
        integers.push_back(i + 1);

    const unsigned perLine{10};
    unsigned n{};
    size_t i{};
    do
    {
        if (integers[i] % 7 && integers[i] % 13) // 运算结果非0即为true,true && true才等于true
        {
            std::cout << std::format("{:<8}", integers[i]);
            n++;
            if (n == perLine)
            {
                std::cout << std::endl;
                n = 0;
            }
        }
    } while (++i < maxInteger);

    std::cout << std::endl;
}