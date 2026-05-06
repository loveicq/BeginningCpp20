// Ex8_12.cpp
// 命令行计算器：支持加减乘除
#include <iostream>
#include <cstdlib> // for atof()

int main(int argc, char *argv[])
{
    // 检查参数数量是否正确
    if (argc != 4)
    {
        std::cout << "用法: Ex8_12.exe <数字1> <运算符> <数字2>" << std::endl;
        std::cout << "示例: Ex8_12.exe 10 + 5" << std::endl;
        return 1; // 返回非零表示错误
    }

    // 解析参数
    double num1 = std::atof(argv[1]); // 字符串转浮点
    char op = argv[2][0];             // 运算符
    double num2 = std::atof(argv[3]);

    // 计算并输出结果
    double result;
    switch (op)
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (num2 == 0)
        {
            std::cout << "错误：除数不能为零！" << std::endl;
            return 1;
        }
        result = num1 / num2;
        break;
    default:
        std::cout << "不支持的运算符: " << op << std::endl;
        return 1;
    }

    std::cout << num1 << " " << op << " " << num2 << " = " << result << std::endl;
    return 0;
}