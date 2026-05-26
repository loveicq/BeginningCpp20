/*************************第8章_练习_第8题************************
    如果使用更加接近数学表示的方式来编写power()函数，那么Ex8_01中，特
别是Ex8_16编写的power()函数本质上是为n>0时计算power(x,n)，如下所示：
    power(x,n)=x*power(x,n-1)
              =x*(x*power(x,n-2))
              =...
              =x*(x*(x*...(x*x)...))
    显然，这种方法需要n-1次乘法操作。读者可能感到意外的是，还有另一种
更高效的方式。假设n是偶数，可知：
    power(x,n)=power(x,n/2)*power(x,n/2)
    因为这个乘法运算的两个操作数是相等的，所以只需要计算这个值一次。
换言之，将power(x,n)的计算缩减为power(x,n/2)，显然后者最多也只需要
进行一半的乘法运算。另外，因为现在可以递归地应用这个公式，所以需要进
行的乘法运算还会更少，准确来说只有log₂(n)次。换句话说，对于1000阶的
数字n，只需要10次乘法运算。读者能否应用这种思想，创建power()函数的
一个更高效的递归版本？可以将Ex8_16.cpp中的程序作为基础。
    注意，在递归算法中经常看到这种原则的应用。在每次递归调用中，都将问
题的规模缩小一半。如果回过头思考一下，会发现我们在快速排序算法中也动用
了相同的原则。这种解决方案非常常见，以至于有了自己名称：分治法。
*****************************************************************/
#include <iostream>
#include <format>

double power(double x, int n);

int main()
{
    for (int i{-3}; i <= 3; ++i)
    {
        std::cout << std::format("{:<10}", power(8.0, i));
        std::cout << std::endl;
    }
}

double power(double x, int n)
{
    if (n == 0)
        return 1.0;
    else if (n > 0)
    {
        double temp = power(x, n / 2);
        if (n % 2 == 0)
            return temp * temp;
        else
            return x * temp * temp;
    }
    else
        return 1.0 / power(x, -n);
}