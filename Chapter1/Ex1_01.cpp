#include <iostream>
// 书中import <iostream>语句在mingw15.1.0中会报错,需改用旧方法包含头文件

int main()
{
    int answer{42};
    std::cout << "The answer to life, the universe, and everything is "
              << answer
              << std::endl;
    std::cin.get(); // 解决调试时CMD窗口一闪而过的问题

    return 0;
}