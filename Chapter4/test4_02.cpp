#include <iostream>

int main()
{
    char coffee{};
    char donuts{};
    char tea{};

    std::cout << "是否有咖啡?<y/n>:";
    std::cin >> coffee;

    std::cout << "是否有甜甜圈?<y/n>:";
    std::cin >> donuts;

    std::cout << "是否有茶叶?<y/n>:";
    std::cin >> tea;

    if (coffee == 'y')
    {
        if (donuts == 'y')
        {
            std::cout << "我们有咖啡和甜甜圈." << std::endl;
        }
        else
        {
            std::cout << "我们有咖啡,但是没有甜甜圈." << std::endl;
        }
    }
    else
    {
        if (tea == 'y')
        {
            std::cout << "我们没有咖啡,但是我们有茶,而甜甜圈……" << std::endl;
        }
        else
        {
            std::cout << "没有茶和咖啡，但是甜甜圈……" << std::endl;
        }
    }
}