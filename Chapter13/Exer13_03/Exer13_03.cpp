// Exer13_03.cpp
/*************************第13章_练习_第3题************************\
查看第2题的答案。如果与我们的参考答案类似，那么应该包含两个二元算术运算符：
一个将两个Box对象相加，另一个将Box对象与数字相乘。虽然将Box对象相减的效果
不好，但是既然有了运算符用来把Box对象与一个整数相乘，难道不想将其与一个
整数相除？而且，创建了每个二元算术运算符op()后，还会希望有对应的复合赋值
运算符op=()。确保使用规范模式实现所有需要的运算符。
\*****************************************************************/
import box;
import <iostream>;

int main()
{
    Box box{2.0, 3.0, 4.0};
    std::cout << "Box is " << box << std::endl;

    size_t n{3};
    box *= 3;
    std::cout << "After multiplying by " << n << " box is " << box << std::endl;

    box /= 3;
    std::cout << "After dividing by " << n << " , the box is again " << box << std::endl;

    Box newBox{2 * box};
    std::cout << "Twice " << box << " is " << newBox << std::endl;

    std::cout << "Half that is again " << (ewBox / 2) << std::endl;

    std::cout << "Adding both boxes gives " << (box + newBox) << std::endl;

    box += newBox;

    std::cout << "The same can be obtained by usign += as well: " << box << std::endl;
}