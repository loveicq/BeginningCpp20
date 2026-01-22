#include <iostream>
#include <format>
#include <vector>
#include <cctype>

int main()
{
    std::vector<size_t> productId;
    std::vector<size_t> quantity;
    std::vector<double> unitPrice;

    for (;;)
    {
        size_t id{};
        size_t number{};
        double price{};

        std::cout << "Please enter the product ID, product quantity and unit price , separated by Spaces:";
        std::cin >> id >> number >> price;

        productId.push_back(id);
        quantity.push_back(number);
        unitPrice.push_back(price);

        char answer{};
        std::cout << "Do we need to add more records?<Y/N>: ";
        std::cin >> answer;
        if (std::toupper(answer) == 'N')
            break;
    }

    double totalPrice{};
    std::cout << std::format("{:14}{:14}{:14}{:14}\n", "Product_Id", "Quantity", "Unit Price", "Cost");
    for (size_t i{}; i < productId.size(); ++i)
    {
        double subtotal{quantity[i] * unitPrice[i]};
        std::cout << std::format("{:<14}{:<14}${:<13.2f}${:<13.2f}\n", productId[i], quantity[i], unitPrice[i], subtotal);
        totalPrice += subtotal;
    }
    std::cout << std::format("{:42}${:<13.2f}", "", totalPrice) << std::endl;
}