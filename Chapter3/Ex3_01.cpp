#include <iostream>
#include <format>

int main()
{

    using namespace std;

    const unsigned int red{0xFF0000u};
    const unsigned int white{0xFFFFFFu};

    cout << "试验使用按位取反、与和或运算符:" << endl;
    cout << format("初始值:            red = {:08X}\n", red);
    cout << format("取反:             ~red = {:08X}\n", ~red);

    cout << format("初始值:          white = {:08X}\n", white);
    cout << format("取反:           ~white = {:08X}\n", ~white);

    cout << format("按位  AND: red & white = {:08X}\n", red & white);
    cout << format("接位   OR: red | white = {:08X}\n", red | white);
    cout << format("\n现在尝试连续进行异或运算:\n");

    unsigned int mask{red ^ white};
    cout << format("mask = red ^ white = {:08X}\n", mask);
    cout << format("        mask ^ red = {:08X}\n", mask ^ red);
    cout << format("      mask ^ white = {:08X}\n", mask ^ white);

    unsigned int flags{0xFF};
    unsigned int bit1mask{0x1};
    unsigned int bit6mask{0b100000};
    unsigned int bit20mask{1u << 19};

    cout << format("使用掩码来选择或设置特定的标志位:\n");
    cout << format("从标志位中选择第1位  : {:08X}\n", flags & bit1mask);
    cout << format("从标志位中选择第6位  : {:08X}\n", flags & bit6mask);
    cout << format("关闭标志位中的第6位  : {:08X}\n", flags &= ~bit6mask);
    cout << format("开启标志位中的第20位 : {:08X}\n", flags |= bit20mask);

    return 0;
}