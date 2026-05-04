// Ex8_04.cpp
// 修改调用者变量的值
#include <iostream>

double changeIt(double *pointer_to_it);
int main()
{
    double it{5.0};
    double result{changeIt(&it)};

    std::cout << "After function execution,it = " << it
              << "\nResult returned is " << result << std::endl;
}

double changeIt(double *pit)
{
    *pit += 10.0;
    std::cout << "Within function,*pit = " << *pit << std::endl;
    return *pit;
}