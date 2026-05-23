/*************************第8章_练习_第5题************************
定义一个函数，检查给定数字是不是质数。不要求检查质数的代码很高效；读者
能够想到的任何算法都可接受。这里重新说明一下，质数是比1大的自然数，除了
1和自身之外，不能被其他正数整除。编写另一个函数，使其生成一个vector<>，
该vector<>中包含从一个数字开始，小于或等于另一个数字的所有自然数。默认
情况下应该从1开始。创建第三个函数，它接收一个数字vector<>作为参数，输
出另一个vector<>，其中包含在输入中找到的所有质数。使用这三个函数创建一
个程序，输出小于或等于用户选择的数字的所有质数（例如，每行输出15个质数）
。注意，原则上，要输出这些质数，并不需要任何vector对象；显然，添加这些
函数只是为了帮助读者多加练习。
*****************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <format>

int check_prime_numbers(int num);
std::vector<int> generate_natural_numbers(int startNum = 1, int endNum = 10);
std::vector<int> filter_primes(const std::vector<int> &naturalNumberVec);
void printNum(const std::vector<int> &primesNum, size_t numPerline);

int main()
{
    int lowerNum{}, maxNum{};
    std::cout << "自然数序列，请输入最小和最大的整数，以空格隔开：";
    std::cin >> lowerNum >> maxNum;
    while (lowerNum <= 1 || maxNum < lowerNum)
    {
        std::cout << "最小数必须 > 1，且最大数必须 >= 最小数：";
        std::cin >> lowerNum >> maxNum;
    }

    std::vector<int> naturalNums{generate_natural_numbers(lowerNum, maxNum)};
    std::vector<int> primeNums{filter_primes(naturalNums)};

    size_t perline{};
    std::cout << "请输入每行要输出的质数个数：";
    std::cin >> perline;
    printNum(primeNums, perline);
}

int check_prime_numbers(int num)
{
    if (num <= 1)
        return 0; // 质数必须大于1，虽然main()中已排队num<=1了
    if (num == 2)
        return 1; // 2是唯一的偶质数
    if (num % 2 == 0)
        return 0; // 偶数(除了2)都不是质数
    for (int i{3}; i * i <= num; i += 2)
        // i*i<=num条件原理：所有因数对都以sqrt(num)为分界线，左边的都≤sqrt(num)，右边的都≥sqrt(num)
        // 如果是i<num条件，效率较低。而且绝对不能是i<=num，否则num%i==0，num是质数也会返回0
        if (num % i == 0)
            return 0;

    return 1;
}

std::vector<int> generate_natural_numbers(int startNum, int endNum)
{
    std::vector<int> naturalNumberVec;
    for (int i{startNum}; i <= endNum; ++i)
        naturalNumberVec.push_back(i);
    return naturalNumberVec;
}

std::vector<int> filter_primes(const std::vector<int> &naturalNumberVec)
{
    std::vector<int> primeVec;
    for (auto a : naturalNumberVec)
        if (check_prime_numbers(a))
            primeVec.push_back(a);
    return primeVec;
}

void printNum(const std::vector<int> &primesNum, size_t numPerline)
{
    if (primesNum.empty())
        return;

    int count_digits{static_cast<int>(std::to_string(primesNum.back()).length()) + 3};
    // 用于控制输出列宽。primeNum已经是有序的，最后一个就是最大数
    size_t perLine{}; // 每行输出个数

    for (auto num : primesNum)
    {
        std::cout << std::format("{:>{}}", num, count_digits);
        if (++perLine == numPerline)
        {
            std::cout << std::endl;
            perLine = 0;
        }
    }
    std::cout << std::endl;
}