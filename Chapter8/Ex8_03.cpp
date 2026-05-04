// Ex8_03.cpp
// 未能修改函数参数的原始值
#include <iostream>
double changeIt(double value_to_be_changed);

int main()
{
    double it{5.0};
    double result{changeIt(it)};

    std::cout << "After function execution,it = " << it
              << "\nResult returned is " << result << std::endl;
}

double changeIt(double it)
{
    it += 10.0;
    std::cout << "Within function,it = " << it << std::endl;
    return it;
}