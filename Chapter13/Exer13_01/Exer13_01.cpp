// Exer13_01.cpp
/*************************第13章_练习_第1题************************\
在示例Ex13_05中，定义Box类中的一个运算符函数，允许Box对象与一个无符号
整数n后乘，得到一个新对象，其高度是原对象的n倍。验证该运算符函数能按预期
的方式工作。
\*****************************************************************/
import <iostream>;
import box;

int main()
{
    Box box{2, 3, 4};
    std::cout << "Box is " << box << std::endl;
    unsigned n{3};
    Box newBox{box * n};
    std::cout << "After multiplying the height by " << n
              << ", the new box is " << newBox << std::endl;
}