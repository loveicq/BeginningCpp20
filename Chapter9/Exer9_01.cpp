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
