// 测试sizeof运算符
#include <iostream>
int main()
{
    int height{74};

    std::cout << "height变量占用" << sizeof height << "字节。" << std::endl;
    std::cout << "\"short\"数据类型占用" << sizeof(short) << "字节。" << std::endl;
    std::cout << "\"int\"数据类型占用" << sizeof(int) << "字节。" << std::endl;
    std::cout << "\"long long\"数据类型占用" << sizeof(long long) << "字节。" << std::endl;
    std::cout << "\"float\"数据类型占用" << sizeof(float) << "字节。" << std::endl;
    std::cout << "\"double\"数据类型占用" << sizeof(double) << "字节。" << std::endl;
    std::cout << "表达式\"height*height/2\"结果占用" << sizeof(height * height / 2) << "字节。" << std::endl;
    std::cin.get();

    return 0;
}