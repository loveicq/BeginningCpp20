// Exer13_07.cpp
/*************************第13章_练习_第7题************************\
实现一个类Rational，使其代表有理数。有理数可表达为两个整数的商或小数n/d，
其中n为整数分子，d为非0的正整数分母。不过，不必担心需要强制分母为非0。那
并不是本练习的目的。创建一个运算符，允许将有理数流输出到std::cout。除此
之外，可以自由选择添加多少个以及添加什么运算符。可以创建运算符来支持两个
有理数以及一个有理数和一个整数的乘法、加法、减法、除法和比较操作。可以
创建运算符来求反、递增或递减有理数。还可以将有理数转换为float或double
类型。对于Rational类，可以定义的运算符有许多。参考代码中的Rational类
支持超过20种不同的运算符，其中许多运算符对多种类型进行了重载。也许读者
可以为Rational类想出更多合理的运算符。不要忘记创建一个程序测试运算符是否
能够正确工作。
\*****************************************************************/
import rational;
import <iostream>;

int main()
{
    Rational x{3, 4};
    Rational y{1, 2};

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    std::cout << "x = " << static_cast<float>(x) << std::endl;
    std::cout << "y = " << static_cast<double>(y) << std::endl;

    std::cout << "-x = " << -x << std::endl;

    std::cout << "x + y = " << x + y << std::endl;
    std::cout << "x - y = " << x - y << std::endl;
    std::cout << "x * y = " << x * y << std::endl;
    std::cout << "x / y = " << x / y << std::endl;

    std::cout << "x + 2 = " << x + 2 << std::endl;
    std::cout << "3 - y = " << 3 - y << std::endl;
    std::cout << "x * 4 = " << x * 4 << std::endl;
    std::cout << "5 / y = " << 5 / y << std::endl;

    std::cout << std::boolalpha; // 输入“true” 和 “false” 代替 1  和 0
    std::cout << "x < y = " << (x < y) << std::endl;
    std::cout << "x > y = " << (x > y) << std::endl;
    std::cout << "x == y = " << (x == y) << std::endl;
    std::cout << "x != y = " << (x != y) << std::endl;
    std::cout << "x >= y = " << (x >= y) << std::endl;
    std::cout << "x <= y = " << (x <= y) << std::endl;

    std::cout << "x < 1 = " << (x < 1) << std::endl;
    std::cout << "2 > y = " << (2 > y) << std::endl;
    std::cout << "x == 3 = " << (x == 3) << std::endl;
    std::cout << "4 != y = " << (4 != y) << std::endl;
    std::cout << "x >= 5 = " << (x >= 5) << std::endl;
    std::cout << "6 <= y = " << (6 <= y) << std::endl;

    std::cout << "x < 1.0 = " << (x < 1.0) << std::endl;
    std::cout << "2 > y = " << (2.0 > y) << std::endl;
    std::cout << "2 == 0.75 = " << (x == 0.75) << std::endl;
    std::cout << "1.5 != y = " << (1.5 != y) << std::endl;
    std::cout << "x >= 5 = " << (x >= 5.0) << std::endl;
    std::cout << "6 >= y = " << (6.0 <= y) << std::endl;

    x += Rational(1, 4);
    std::cout << "x += 1/4 --> x = " << x << std::endl;
    x *= 2;
    std::cout << "x *= 2 --> x = " << x << std::endl;

    y += 1;
    std::cout << "y += 1 --> y = " << y << std::endl;

    std::cout << "y++ = " << y++ << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "--y = " << --y << std::endl;
}