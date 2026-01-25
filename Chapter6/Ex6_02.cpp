#include <iostream>
#include <format>

int main()
{
    int unit_price{295};
    int count{};
    int discount_threshold{25};
    double discount{0.07};

    int *pcount{&count};
    std::cout << "Enter the number of items you want: ";
    std::cin >> *pcount;
    std::cout << std::format("The unit price is ${:.2f}\n", unit_price / 100.0);

    int *punit_price{&unit_price};
    int price{*pcount * *punit_price};
    auto *pprice{&price};

    double net_price{};
    double *pnet_price{nullptr};
    pnet_price = &net_price;
    if (*pcount > discount_threshold)
    {
        std::cout << std::format("You qualify for a discount of {:.0f} percent.\n", discount * 100);
        *pnet_price = price * (1 - discount) / 100;
    }
    else
    {
        net_price = *pprice / 100;
    }
    std::cout << std::format("The net price for {} items is ${:.2f}\n", *pcount, net_price);
}