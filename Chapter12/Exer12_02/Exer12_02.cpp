// Exer12_02.cpp
/*************************第12章_练习_第2题************************
修改上一题中的Integer类，使得不提供实参也可以创建Integer对象。此时，成
员变量的值应该被初始化为0。读者是否能够想出两种方法来实现此需求？另外，
实现一个副本构造函数，当调用该副本构造函数时，输出一条信息。
然后，编写一个成员函数，比较当前对象和作为实参传递的Integer对象。如果当
前对象小于实参，该函数就返回-1；如果它们相等，就返回0；如果当前对象大于
实参，就返回1.测试Integer类的两个版本：第一个版本的compare()函数的实
参按值传递；第二个版本的compare()函数的实参按引用传递。在调用时，构造
函数会输出什么结果？解释出现这种结果的原因。在类中，不能同时这两个函数
作为重载函数，为什么？
*****************************************************************/
import integer;
import <iostream>;

int main()
{
    std::cout << "Create i with the value 0." << std::endl;
    Integer i;
    i.show();
    std::cout << "Change value of i to 15." << std::endl;
    i.setValue(15);
    i.show();

    std::cout << "Create j from object i." << std::endl;
    Integer j{i};
    j.show();
    std::cout << "Set value of j to 150 times that of i." << std::endl;
    j.setValue(150 * i.getValue());
    j.show();

    std::cout << "Create k with the value 789." << std::endl;
    Integer k{789};
    k.show();
    std::cout << "Set value of k to sum of i and j values." << std::endl;
    k.setValue(i.getValue() + j.getValue());
    k.show();

    std::cout << "Result of comparing i and j is " << i.compare(j) << std::endl;
    std::cout << "Result of comparing k and j is " << k.compare(j) << std::endl;
}