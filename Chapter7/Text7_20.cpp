// 8.6.2 返回引用
#include <iostream>
#include <string>
int main()
{
    std::string &larger(std::string & s1, std::string & s2);

    std::string str1("abcx");
    std::string str2("adcf");
    larger(str1, str2) = "defg"; // 通过返回引用,可以在赋值操作的左边使用函数调用
    std::cout << "str1=" << str1 << "\nstr2=" << str2 << std::endl;
}

// 此函数参数不能是const引用，因为返回类型是非const引用。
// 如果参数是const，返回类型也必须是const，就不能在赋值左边使用了。
std::string &larger(std::string &s1, std::string &s2)
{
    return s1 > s2 ? s1 : s2;
}