//Ex12_10.cpp
//重载const
import <iostream>;
import Box;

int main()
{
    const Box constBox{ 1,2,3 };
    //constBox.length() = 2;    //不编译：好！
    std::cout << constBox.length() << std::endl;

    Box nonConstBox{ 3,2,1 };
    nonConstBox.length() *= 2;
    std::cout << nonConstBox.length() << std::endl;
}