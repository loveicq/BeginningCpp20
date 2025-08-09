// 使用字符变量
#include <iostream>
#include <format>

int main()
{
    using std::cout;
    using std::endl;
    using std::format;

    char ch{'A'}; // 字面量字符
    cout << format("ch = {}\n", ch);
    /*下面语句{ch+2}会先把ch隐式转换成int,完成计算,再把int转换成char,
    所以编译器会有窄化转换的提醒（narrowing conversion）。采用其它方式
    则不会有窄化转换提醒了，如：
    1.char letter{ static_cast<char>(ch + 2) };
    2.char letter(ch + 2);
    3.char letter = ch + 2;*/
    char letter{ch + 2};
    cout << "letter = " << letter << endl;
    ++ch;
    cout << format("ch = {}\n", ch);
    ch += 3;
    cout << format("ch is '{0}' which is code {0:#x}\n", ch);
    ch = 33; // 十进制字符
    cout << "ch = " << ch << endl;
    ch = '\x46'; // 十六进制字符
    cout << format("ch = {}\n", ch);
    ch = '\77'; // 八进制字符
    cout << "ch = " << ch << endl;

    return 0;
}