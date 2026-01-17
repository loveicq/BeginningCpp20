#include <iostream>
#include <format>
#include <cctype>

int main()
{
    constexpr auto header_format = "{:^11}{:^11}{:^11}{:^11}\n";
    constexpr auto body_format = "{0:^11}{1:^11d}{1:^11X}{1:^11b}\n";

    std::cout << std::format(header_format, "Character", "Decimal", "Hexadecimal", "Binary");

    for (int ch{}; ch <= 127; ++ch)
    {
        if (!std::isprint(static_cast<char>(ch)))
        {
            continue;
        }
        std::cout << std::format(body_format, static_cast<char>(ch), ch);
    }
}