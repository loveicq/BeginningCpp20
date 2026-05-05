// Ex8_07.cpp
// 修改调用者变量的值 - 引用与指针
#include <iostream>

void change_it_by_pointer(double *reference_to_it);   // 传递指针（按值传递）
void change_it_by_reference(double &reference_to_it); // 按引用传递

int main()
{
    double it{5.0};

    change_it_by_pointer(&it); // 现在我们传递地址
    std::cout << "After first function execution,it = " << it << std::endl;

    change_it_by_reference(it); // 现在我们传递引用，而不是值！
    std::cout << "After second function execution,it = " << it << std::endl;
}

void change_it_by_pointer(double *pit)
{
    *pit += 10.0; // 这会修改原始的double值
}
void change_it_by_reference(double &pit)
{
    pit += 10.0; // 这也会修改原始的double值！
}