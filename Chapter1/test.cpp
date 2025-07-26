// 这段代码测试不同进制整数的混合运算,结果表明c++会自动转换数制,并且前缀、后缀和分隔符不影响运算。
#include <iostream>
int main()
{
    // 列表初始化时可以采用表达式,并且可以直接用不同数制的字面量整数
    long long finalResult{22'333uLL + 0xFF00FF00u + 0765321L + 0b110010101101U};
    std::cout << "22'333uLL + 0xFF00FF00u + 0765321L + 0b110010101101U = " << finalResult << std::endl;
    std::cin.get();
    return 0;
}