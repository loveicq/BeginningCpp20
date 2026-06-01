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
    if (data.empty()) // 空数据直接返回，防止后面*取值出错
        return data;

    // 此题教材答案有bug
    // 先取出最小和最大值，因为shift_range()函数会改变原数据
    // 后面scale_range()的参数得到的是修改后的数据
    auto minValue = smallest(data);
    auto maxValue = largest(data);

    shift_range(data, -*minValue); // std::optional的值需要*取出
    return scale_range(data, *maxValue);
}