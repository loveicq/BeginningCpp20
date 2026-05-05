// Ex8_11.cpp
// Using multiple default parameter
#include <iostream>
#include <format>
#include <string>

void show_data(const int data[], size_t count = 1,
               const std::string &title = "Data Values",
               size_t width = 10, size_t perline = 5);

int main()
{
    int samples[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int dataItem{-99};
    show_data(&dataItem);

    dataItem = 13;
    show_data(&dataItem, 1, "Unlucky for some!");

    show_data(samples, std::size(samples));
    show_data(samples, std::size(samples), "Samples");
    show_data(samples, std::size(samples), "Samples", 6);
    show_data(samples, std::size(samples), "Samples", 8, 4);
}

void show_data(const int data[], size_t count,
               const std::string &title,
               size_t width, size_t perline)
{
    std::cout << title << std::endl;
    for (size_t i{}; i < count; ++i)
    {
        std::cout << std::format("{:{}}", data[i], width);
        if ((i + 1) % perline == 0)
            std::cout << '\n';
    }
    std::cout << std::endl;
}