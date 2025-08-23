#include <iostream>
#include <bitset> //用于bitset直接输出二进制

int main()
{
    using namespace std;

    unsigned short font{0x064C};
    unsigned short sizeMask{0x1F};
    unsigned short styleMask{0xFF00};
    unsigned short italicMask{0xFF3F};
    // 0x064C=ob0000'0110'0100'1100
    // 0x1F=0b0001'1111
    // 0xFF00=0b1111'1111'0000'0000
    // 0xFF3F=0b1111'1111'0011'1111
    // 从C++14开始，还可以直接使用二进制字面量赋值：unsigned short font {0b00000110'0'10'01100};

    auto size{static_cast<unsigned short>(font & sizeMask)};            // 求字号
    auto style{static_cast<unsigned short>((font & styleMask) >> 8)};   // 求字体
    auto non_italic‌{static_cast<unsigned short>(font & italicMask)}; // 关闭斜体位

    cout << "size = " << size << endl
         << "style = " << style << endl
         << "non_italic‌ = ob" << bitset<16>(non_italic‌) << endl;

    return 0;
}