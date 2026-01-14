#include <iostream>
#include <array>

int main()
{
    // 使用两对大括号分为两个作用域，these、those和them就变为局部变量，解决变量命名冲突问题
    {
        std::cout << "First we try out the comparison operators for std::array<> objects:" << std::endl;

        std::array these{1.0, 2.0, 3.0, 4.0};
        std::array those{1.0, 2.0, 3.0, 4.0};
        std::array them{1.0, 1.0, 5.0, 5.0};

        if (these == those)
            std::cout << "these and those are equal." << std::endl;
        if (those != them)
            std::cout << "those and them are not equal." << std::endl;
        if (those > them)
            std::cout << "those are greater than them." << std::endl;
        if (them < those)
            std::cout << "them are less than those." << std::endl;
    }

    std::cout << std::endl;

    {
        std::cout << "Next we repeat exactly the same comparisons with plain C++ arrays:" << std::endl;

        double these[]{1.0, 2.0, 3.0, 4.0};
        double those[]{1.0, 2.0, 3.0, 4.0};
        double them[]{1.0, 1.0, 5.0, 5.0};

        if (these == those)
            std::cout << "these and those are equal." << std::endl;
        if (those != them)
            std::cout << "those and them are not equal." << std::endl;
        if (those > them)
            std::cout << "those are greater than them." << std::endl;
        if (them < those)
            std::cout << "them are less than those." << std::endl;
    }
}