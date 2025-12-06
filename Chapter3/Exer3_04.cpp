#include <iostream>
#include <format>
#include <string>

// 函数：将整数格式化为二进制，每8位一组
std::string binary_with_separator(unsigned int value, int group_size = 8)
{
    const int total_bits = sizeof(value) * 8;
    std::string result;

    for (int i = total_bits - 1; i >= 0; i--)
    {
        result += (value >> i) & 1 ? '1' : '0';

        // 每 group_size 位添加分隔符（但不在开头和结尾）
        if (i > 0 && i % group_size == 0)
        {
            result += ' ';
        }
    }

    return result;
}

int main()
{
    unsigned packed{};
    unsigned char ch{};

    std::cout << std::format("{:16}", "请输入第1个字母:");
    std::cin >> ch;
    packed |= ch;
    packed <<= 8;

    std::cout << std::format("{:16}", "请输入第2个字母:");
    std::cin >> ch;
    packed |= ch;
    packed <<= 8;

    std::cout << std::format("{:16}", "请输入第3个字母:");
    std::cin >> ch;
    packed |= ch;
    packed <<= 8;

    std::cout << std::format("{:16}", "请输入第4个字母:");
    std::cin >> ch;
    packed |= ch;

    std::cout << "  这个字符串的二进制码是:0b" << binary_with_separator(packed, 8) << std::endl;
    std::cout << std::format("这个字符串的十六进制码是:{:#0x}\n", packed);

    unsigned int mask{0xff};

    std::cout << "      这个字符串反序输出:";

    ch = static_cast<char>(packed & mask);
    std::cout << ch;
    ch = static_cast<char>(packed >> 8 & mask);
    std::cout << ch;
    ch = static_cast<char>(packed >> 16 & mask);
    std::cout << ch;
    ch = static_cast<char>(packed >> 24 & mask);
    std::cout << ch << std::endl;

    return 0;
}