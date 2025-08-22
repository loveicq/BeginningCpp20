// 按位移动不带符号的整数示例
#include <iostream>

using namespace std;

int main()
{
    unsigned short number{16387};
    auto result{static_cast<unsigned short>(number << 2)};
    /*
    16387=0b0100000000000011
    0b0100000000000011 << 2 = 0b0000000000001100
    0b0000000000001100 = 12
    */
    cout << result << endl;

    return 0;
}