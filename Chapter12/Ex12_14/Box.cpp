//Box.cpp
module box;
import <iostream>;

Box::Box()  //默认构造函数
{
    ++s_object_count;
    std::cout << "Default Box constructor called." << std::endl;
}
Box::Box(double side) : Box{ side,side,side } //立方体构造函数
{
    // 不要在委托构造函数中增加 s_object_count：
    // 该计数器已在被委托的构造函数中增加过了！
    std::cout << "Box constructor 2 called." << std::endl;
}
Box::Box(const Box& box)    //副本构造函数
    : m_length{ box.m_length }, m_width{ box.m_width }, m_height{ box.m_height }
{
    ++s_object_count;
    std::cout << "Box copy constructor called." << std::endl;
}
Box::Box(double length, double width, double height)
    : m_length{ length }, m_width{ width }, m_height{ height }
{
    ++s_object_count;
    std::cout << "Box constructor 1 called." << std::endl;
}