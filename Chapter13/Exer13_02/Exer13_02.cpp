// Exer13_02.cpp
/*************************第13章_练习_第2题************************\
定义一个运算符函数，允许Box对象与一个无符号整数n前乘，得到与第1题相同的
结果。验证该运算符函数能按预期的方式工作。
\*****************************************************************/
import box;
import <iostream>;

int main()
{
    Box box{2.0, 3.0, 4.0};
    std::cout << "Box is " << box << std::endl;
    unsigned n{3};
    Box newBox{n * box};
    std::cout << "After multiplying the height by " << n << ", the new box is " << newBox << std::endl;
}