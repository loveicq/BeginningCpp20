#include <iostream>

int main()
{
    int age{};
    int income{};
    int balance{};

    std::cout << "请输入你的年龄:";
    std::cin >> age;
    std::cout << "请输入你的年收入:";
    std::cin >> income;
    std::cout << "请输入你的银行存款:";
    std::cin >> balance;

    if (age >= 21 && (income > 25'000 || balance > 100'000))
    {
        int loan{};
        if (2 * income < balance / 2)
        {
            loan = 2 * income;
        }
        else
        {
            loan = balance / 2;
        }
        std::cout << "\n你可以贷" << loan << "美元." << std::endl;
    }
    else
    {
        std::cout << "\n很抱歉,你没有贷款资格." << std::endl;
    }
}