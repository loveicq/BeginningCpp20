#include <iostream>
#include <format>
#include <cctype>

int main()
{
    constexpr auto header_format = "{:^11}{:^11}{:^11}{:^11}\n";
    constexpr auto body_format = "{0:^11}{0:^11X}{0:^11d}{0:^11b}\n";

    std::cout << std::format(header_format, "Character", "Hexadecimal", "Decimal", "Binary");
    char ch{};
    do
    {
        if (!std::isprint(ch))
        {
            continue;
        }
        std::cout << std::format(body_format, ch);
    } while (ch++ < 127);
}