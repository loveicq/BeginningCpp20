#include <iostream>
#include <bitset>

int main()
{
    using namespace std;

    unsigned short font{0x064c};
    auto italic{static_cast<unsigned short>(1U << 6)};
    auto bold{static_cast<unsigned short>(1U << 5)};

    cout << "Initial font value: " << bitset<16>(font) << " (hex: 0x" << hex << font << dec << ")" << endl; // hex、dec,流控制符，先转十六进制输出，再转回十进制
    cout << "Italic bit mask:    " << bitset<16>(italic) << endl;
    cout << "Bold bit mask:      " << bitset<16>(bold) << endl
         << endl;

    // 关闭斜体
    unsigned short withoutItalic = font & ~italic;
    cout << "Without italic:     " << bitset<16>(withoutItalic) << endl;

    // 关闭粗体
    unsigned short withoutBold = font & ~bold;
    cout << "Without bold:       " << bitset<16>(withoutBold) << endl;

    // 关闭斜体和粗体
    unsigned short withoutBoth = font & ~(italic | bold);
    cout << "Without both:       " << bitset<16>(withoutBoth) << endl;

    // 另一种方式关闭斜体和粗体
    unsigned short withoutBoth2 = font & ~italic & ~bold;
    cout << "Without both (alt): " << bitset<16>(withoutBoth2) << endl;

    return 0;
}