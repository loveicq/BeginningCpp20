// Ex13_04.cpp
import box;
import <iostream>;
import <format>;
import <string_view>;
import <vector>;

int main()
{
    const std::vector boxes{Box{2.0, 1.5, 3.0}, Box{1.0, 3.0, 5.0},
                            Box{1.0, 2.0, 1.0}, Box{2.0, 3.0, 2.0}};
    const Box theBox{3.0, 1.0, 4.0};

    for (const auto& box : boxes)
        if (theBox > box)
            std::cout << theBox << " is greater than " << box << std::endl;

    std::cout << std::endl;

    for (const auto& box : boxes)
        if (theBox != box)
            std::cout << theBox << " is not equal to " << box << std::endl;

    std::cout << std::endl;

    for (const auto& box : boxes)
        if (6.0 <= box)
            std::cout << "6 is less than or equal to " << box << std::endl;
}