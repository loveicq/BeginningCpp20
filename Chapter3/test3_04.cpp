#include <iostream>
#include <bitset>

int main()
{
    using namespace std;

    unsigned short font{0x064C};
    auto italic{0b1111'1111'1011'1111};
    auto bold{static_cast<unsigned short>(1u << 5)};
    // 1u=1 unsigned，常量，表示无符号整数1
    cout << "           font = " << bitset<16>(font) << endl
         << "fontCloseItalic = " << bitset<16>(font & italic) << endl
         << "   fontOpenBold = " << bitset<16>(font | bold) << endl;

    return 0;
}