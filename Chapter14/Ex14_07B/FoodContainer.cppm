// FoodContainer.cppm
export module food;

import <string>;
import <string_view>;
import <iostream>;

export class FoodContainer
{
public:
    FoodContainer()
    {
        std::cout << "FoodContainer() called.\n";
    }

    FoodContainer(std::string_view name) : name{name}
    {
        std::cout << "FoodContainer(string_view) called.\n";
    }

    FoodContainer(std::string_view name, double density, double volume)
        : name{name}, density{density}, volume{volume}
    {
        std::cout << "FoodContainer(string_view,double,double) called.\n";
    }

    ~FoodContainer()
    {
        std::cout << "FoodContainer destructor" << std::endl;
    }

    double getWeight() const
    {
        return volume * density;
    }

protected:
    std::string name{"cereal"};
    double volume{};
    double density{0.03};
};