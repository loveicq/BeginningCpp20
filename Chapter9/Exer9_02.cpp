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