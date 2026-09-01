// Ex13_07.cpp
module integer;

import <iostream>;

int main()
{
    const Integer i{1};
    const Integer j{2};
    const auto result = (i * 2 + 4 / j - 1) % j;
    // 因Integer构造函数没有explicit关键字，而+-*/%重载要求左、右操作数为Integer对象，
    // 所以上面表达式的整数隐式转换为Integer对象了
    std::cout << result.getValue() << std::endl;
}