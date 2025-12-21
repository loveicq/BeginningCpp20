#include <iostream>

int main()
{
    const unsigned quarter{25};
    const unsigned dime{10};
    const unsigned nickel{5};
    double amountInDollars{0.0};

    std::cout << std::endl
              << "Please enter a cash amount between 0 and 10 dollars:$";
    std::cin >> amountInDollars;

    if (amountInDollars >= 0.0 && amountInDollars <= 10.0) // 如果在0-10美元之间则执行
    {
        // 美元换算成美分
        auto amountInCents{static_cast<unsigned>(amountInDollars * 100.0 + 0.5)};

        // 计算25美分数量
        const auto quarters{amountInCents / quarter};
        amountInCents %= quarter;

        // 计算10美分数量
        const auto dimes{amountInCents / dime};
        amountInCents %= dime;

        // 计算5美分数量
        const auto nickels{amountInCents / nickel};
        const auto pennies{amountInCents % nickel};

        // 输出换算结果,并且体现单数和复数的语法
        std::cout << std::endl
                  << "The dollar value $" << amountInDollars << " can be broken down into:" << std::endl
                  << quarters << "quarter" << (quarters > 1 ? "s" : "") << "," << std::endl
                  << dimes << "dime" << (dimes > 1 ? "s" : "") << "," << std::endl
                  << nickels << "nickel" << (nickels > 1 ? "s" : "") << "," << std::endl
                  << pennies << "penn" << (pennies > 1 ? "ies" : "y") << "." << std::endl;
    }
    else
    {
        // 如果不在0-10美元之间,则提醒错误,退出程序
        std::cout << std::endl
                  << "You didn't enter an amount between $0 and $10." << std::endl;
    }
}