// 第5题
#include <iostream>
#include <format>
#define formatString "{:^4}的三原色为:红:{:^3},绿:{:^3},蓝:{:^3}\n"

int main()
{
    enum class Color : unsigned
    {
        Red = 0xff0000u,
        Green = 0x00ff00u,
        Yellow = 0xffff00u,
        Purple = 0xff00ffu,
        Blue = 0x0000ffu,
        Black = 0x000000u,
        White = 0xffffffu
    };

    Color yellow{Color::Yellow};
    Color purple{Color::Purple};
    Color green{Color::Green};

    std::cout << std::format(formatString,
                             "黄色",
                             (static_cast<unsigned>(yellow) & static_cast<unsigned>(Color::Red)) >> 16,
                             (static_cast<unsigned>(yellow) & static_cast<unsigned>(Color::Green)) >> 8,
                             static_cast<unsigned>(yellow) & static_cast<unsigned>(Color::Blue));

    std::cout << std::format(formatString,
                             "紫色",
                             (static_cast<unsigned>(purple) & static_cast<unsigned>(Color::Red)) >> 16,
                             (static_cast<unsigned>(purple) & static_cast<unsigned>(Color::Green)) >> 8,
                             static_cast<unsigned>(purple) & static_cast<unsigned>(Color::Blue));

    std::cout << std::format(formatString,
                             "绿色",
                             (static_cast<unsigned>(green) & static_cast<unsigned>(Color::Red)) >> 16,
                             (static_cast<unsigned>(green) & static_cast<unsigned>(Color::Green)) >> 8,
                             static_cast<unsigned>(green) & static_cast<unsigned>(Color::Blue));

    return 0;
}