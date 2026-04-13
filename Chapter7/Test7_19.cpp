// 测试Unicode字符串对象
#include <iostream>
#include <string>

int main()
{
    // 注意声明和赋值的关键字
    std::u8string u8{u8"u8string！你好，中文!"}; // UTF-8
    std::u16string u16{u"u16string!"};           // UTF-16
    std::u32string u32{U"u32string!"};           // UTF-32

    // Unicode字符串对象需要转换才能输出，这样转换可以输出UTF-8编码的中文
    std::string s(reinterpret_cast<const char *>(u8.data()), u8.size());
    std::cout << s << std::endl;

    // 或者用范围循环输出每个字符
    for (char16_t c : u16)
    {
        std::cout << static_cast<char>(c);
    }
    std::cout << std::endl;

    for (char32_t c : u32)
    {
        std::cout << static_cast<char>(c);
    }
    std::cout << std::endl;
}