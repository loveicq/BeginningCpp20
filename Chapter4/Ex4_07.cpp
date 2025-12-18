#include <iostream>
#include <format>

int main()
{
    int mice{};
    int brown{};
    int white{};

    std::cout << "How many brown mice do you have?";
    std::cin >> brown;
    std::cout << "How many white mice do you have?";
    std::cin >> white;

    mice = brown + white;

    std::cout << std::format("You have {} {} in total.\n", mice, mice == 1 ? "mouse" : "mice");
}