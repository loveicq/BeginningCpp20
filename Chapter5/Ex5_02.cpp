#include <iostream>
#include <iterator> //为了可移植,应显式包含此头文件,而不是包含<array>,或者不包含(虽然在GCC15.1.0中不包含也可以编译通过)

int main()
{
    int values[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    std::cout << "There are " << std::size(values) << " elements in the array." << std::endl;

    auto sum{0};
    const size_t old_school_size = sizeof(values) / sizeof(values[0]);
    for (size_t i{}; i < old_school_size; ++i)
    {
        sum += values[i];
    }
    std::cout << "The array have " << old_school_size << " elements.\n"
              << "The sum of the array elements is " << sum << "." << std::endl;
}