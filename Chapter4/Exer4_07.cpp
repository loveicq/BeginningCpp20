#include <iostream>
#include <format>
#include <cctype>

int main()
{
    char letter{};
    std::cout << "Enter a letter: ";
    std::cin >> letter;

    // 如果字符不是字母则退出程序
    if (!std::isalpha(letter))
    {
        std::cout << "That's not a letter!" << std::endl;
        return 1;
    }

    // 判断字符是不是元音字母
    const auto lowerCaseLetter{std::tolower(letter)};
    std::cout << "'" << letter << "' is a ";
    switch (lowerCaseLetter)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        std::cout << "vowel.";
        break;
    default:
        std::cout << "consonant.";
        break;
    }
    std::cout << std::endl;

    // 判断字符是小写还是大写,并输出信息
    std::cout << "'" << letter << "' is "
              << (std::islower(letter) ? "lowercase." : "uppercase.")
              << std::endl;

    // 输出字符编码的二进制值
    std::cout << "The binary code for '" << static_cast<char>(lowerCaseLetter) << "' is 0b"
              << ((lowerCaseLetter & 0b1 << 7) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 6) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 5) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 4) ? 1 : 0)
              << "'"
              << ((lowerCaseLetter & 0b1 << 3) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 2) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 1) ? 1 : 0)
              << ((lowerCaseLetter & 0b1 << 0) ? 1 : 0)
              << "."
              << std::endl;

    // 用format格式化输出二进制数值
    std::cout << "Use the format() to represent the letter in binary is " << std::format("{:#010b}.", lowerCaseLetter) << std::endl;
}