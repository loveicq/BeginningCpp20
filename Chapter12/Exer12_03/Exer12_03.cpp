// Exer12_03.cpp
/*************************第12章_练习_第3题************************
为Integer类实现成员函数add()、subtract()和multiply()，对当前对象和
Integer类型的参数值进行加法、减法和乘法运算。用main()演示类中这些函数的
操作，创建几个封装了整数值的Integer对象，再使用这些对象计算4*5^3 +
6*5^2 + 7*5 + 8的值。实现这些函数，使计算和结果的输出在一条语句中完成。
*****************************************************************/
import integer;
import <iostream>;
int main()
{
    const Integer four{4};
 Integer six{6};
    const Integer eight{8};

    Integer result{four};
    std::cout << "Result is "
              << result.multiply(5).add(six).multiply(5).add(7).multiply(5).add(eight).getValue()
              << std::endl;
    /*
    4*5^3 + 6*5^2 + 7*5 + 8 = ((4*5+6)*5+7)*5+8
    result.multiply(5);等价于result.multiply(Integer(5));
    只要类有一个非 explicit 的单参数构造函数，C++ 就允许从参数类型到类类型的隐式转换。
    */
}