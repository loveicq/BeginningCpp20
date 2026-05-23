/*************************第8章_练习_第4题************************
创建一个函数plus()，它把两个数值加在一起，返回它们的和。提供处理int、
double和string类型的重载版本，测试它们是否能处理下面的调用：
const int n {plus(3,4)};
const double d {plus(3.2,4.2)};
const string s {plus("he","llo")};
const string s1 {"aaa"};
const string s2 {"bbb"};
const string s3 {plus(s1,s2)};
为什么下面的调用不工作？
const auto d {plus(3,4.2)};
*****************************************************************/
#include <iostream>
#include <string>

int add(int a, int b);
double add(double a, double b);
std::string add(const std::string &str1, const std::string &str2);
// 记得std::string类型要用&!!!

int main()
{
    const int n{add(3, 4)};
    const double d{add(3.2, 4.2)};
    const std::string s{add("he", "llo")};

    const std::string s1{"aaa"};
    const std::string s2{"bbb"};
    const std::string s3{add(s1, s2)};

    // const auto d{add(3, 4.2)};//参数类型不匹配任何重载版本

    std::cout << "add(3, 4) = " << n << std::endl;
    std::cout << "add(3.2, 4.2) = " << d << std::endl;
    std::cout << "add(\"he\",\"llo\") = " << s << std::endl;
    std::cout << "当变量s1 = \"aaa\"，变量s2 = \"bbb\"时，";
    std::cout << "add(s1, s2) = " << s3 << std::endl;
}

int add(int a, int b) { return a + b; }

double add(double a, double b) { return a + b; }

std::string add(const std::string &str1, const std::string &str2) { return str1 + str2; }