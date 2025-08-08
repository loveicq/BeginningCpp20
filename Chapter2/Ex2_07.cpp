// Ex2_07.cpp
// Finding maximum and minimum values for data types
#include <iostream>
#include <format>
#include <limits>
#include <stdio.h>
#include <float.h>
using std::cout;
using std::endl;
using std::format;
using std::numeric_limits;

int main()
{
    printf("The range for type short is from %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("The range for type float is from %e to %e\n", FLT_MIN, FLT_MAX);

    cout << format("The range for type short is from {} to {}\n",
                   numeric_limits<short>::min(), numeric_limits<short>::max())
         << format("The range for type unsigned int is from {} to {}\n",
                   numeric_limits<unsigned int>::min(), numeric_limits<unsigned int>::max())
         << format("The range for type long is from {} to {}\n",
                   numeric_limits<long>::min(), numeric_limits<long>::max())
         << format("The range for type float is from {} to {}\n",
                   numeric_limits<float>::min(), numeric_limits<float>::max())
         << format("The range for type float is from {} to {}\n",
                   numeric_limits<float>::lowest(), numeric_limits<float>::max())
         << format("The range for type double is from {} to {}\n",
                   numeric_limits<double>::min(), numeric_limits<double>::max())
         << format("The range for type double is from {} to {}\n",
                   numeric_limits<double>::lowest(), numeric_limits<double>::max())
         << format("The range for type long double is from {} to {}\n",
                   numeric_limits<long double>::min(), numeric_limits<long double>::max())
         << format("The range for type long double is from {} to {}\n",
                   numeric_limits<long double>::lowest(), numeric_limits<long double>::max());

    return 0;
}