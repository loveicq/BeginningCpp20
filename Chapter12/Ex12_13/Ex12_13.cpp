//Ex12_13.cpp
import <iostream>;
import box;

int main()
{
    const Box box1{ 2.0,3.0,4.0 };
    Box box2{ 5.0 };
    std::cout << "box1 volume = " << box1.volume() << std::endl;
    std::cout << "box2 volume = " << box2.volume() << std::endl;
    Box box3{ box2 };
    std::cout << "box3 volume = " << box3.volume() << std::endl;

    std::cout << std::endl;

    Box boxes[6]{ box1,box2,box3,Box{2.0} };    //最后两个函数没有指定初始值，所以编译器调用默认构造函数来创建它们
}