#include <iostream>
#include <format>

int main()
{
    using namespace std;

    unsigned short font{0x064c};
    auto bold{static_cast<unsigned short>(1U << 5)};
    cout << format("     font = {:016b}\n     bold = {:016b}\n", font, bold);
    font ^= bold;
    cout << format("font^bold = {:016b}\n", font);

    return 0;
}