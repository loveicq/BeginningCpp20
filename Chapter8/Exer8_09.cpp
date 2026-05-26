/*************************第8章_练习_第9题************************
修改第8题的解决方案，使其统计调用power(1.5,1000)时执行的乘法次数。将
每个乘法运算替换为一个辅助函数mult()，该函数接收两个实参，输出一条消息
来说明已经执行了多少次乘法运算，然后返回两个实参的乘积。请使用至少一个
静态变量。
*****************************************************************/
#include <iostream>

double mult(double a, double b);
double power(double x, int n);

int main()
{
    double result = power(1.5, 1000);
    std::cout << "结果：" << result << std::endl;
}

double mult(double a, double b)
{
    static int count = 0;

    count++;
    std::cout << "第 " << count << " 次乘法运算" << std::endl;

    return a * b;
}

double power(double x, int n)
{
    if (n == 0)
        return 1.0;
    else if (n > 0)
    {
        double temp = power(x, n / 2);
        if (n % 2 == 0)
            return mult(temp, temp);
        else
            return mult(mult(x, temp), temp);
    }
    else
        return mult(1.0, power(x, -n));
}