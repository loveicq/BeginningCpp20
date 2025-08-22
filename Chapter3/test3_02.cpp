// 按位移动带符号的整数示例
#include <iostream>
#include <format>

int main()
{
    using namespace std;

    signed char positive{+104};
    signed char negative{-104};
    /*
    +104=0b01101000
    -104=0b10011000//01101000➡10010111(反码)➡10011000(补码)
    */
    cout << format("+104右移两位是{:+},-104右移两位是{:+}。\n",
                   static_cast<signed char>(positive >> 2),  //+26
                   static_cast<signed char>(negative >> 2)); //-26
    cout << format("+104左移两位是{:+},-104左移两位是{:+}。\n",
                   static_cast<signed char>(positive << 2),
                   // 原本应是+416，因char字节不足，舍弃前面两位，变成-96，符号也改变了
                   static_cast<signed char>(negative << 2));
    // 原本应是-416，因char字节不足，舍弃前面两位，变成+96，符号也改变了

    return 0;
}