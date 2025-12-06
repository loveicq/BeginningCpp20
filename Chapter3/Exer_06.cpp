/*
异或^规律:
1.任何数与自己异或结果为0,即a^a=0;
2.任何数与0异或结果为自己,即a^0=a;
3.异或运算满足结合律和交换律,即a^b^c=a^(b^c),a^b=b^a;
*/

#include <iostream>

int main()
{
    int a{5};
    int b{10};

    std::cout << "交换前a = " << a << " , b = " << b << std::endl;

    a = a ^ b;
    b = a ^ b; // a展开,算式为b=(a^b)^b=a^0=a
    a = a ^ b; // a和b展开,算式为a=(a^b) ^ [(a^b)^b]=(a^a)^(b^b)^b=0^0^b=0^b=b

    std::cout << "交换后a = " << a << " , b = " << b << std::endl;

    return 0;
}