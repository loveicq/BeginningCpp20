// Exer13_04.cpp
/*************************第13章_练习_第4题************************\
如果允许my_box <= 6.0和6.0 <= my_box ，那么为什么不允许my_box = 6.0和
6.0 != my_box?需要使用多少个运算符函数来实现这样的重载呢？扩展Ex13_04中
的Box类，试着使用最新的运算符
\*****************************************************************/
import box;
import <iostream>;

int main()
{
    Box box1{1.0, 2.0, 3.0};
    Box box2{3.0, 2.0, 1.0};
    Box box3{1.0, 2.0, 3.0};

    std::cout << "box1 and box2 are " << (box1 == box2 ? "" : "not ") << "equal\n";
    std::cout << "box1 and box3 are " << (box1 != box3 ? "not " : "") << "equal\n";
    std::cout << "box1 is " << (box1 == 6.0 ? "" : "not ") << "equal to 6.0\n";
    std::cout << "10.0 is " << (10 != box2 ? "not " : "") << "equal to box2\n";
}