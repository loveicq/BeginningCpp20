/*************************第8章_练习_第7题************************
计算机科学家介绍递归时介绍递归时，非常喜欢使用所谓的斐波那契函数。斐波那契函
数计算著名的斐波那契数列中的第n个值。这是一个正整数序列，其特征是前两个数字
之后的每个数字都是之前的两个数字之和。对于n≥1,该序列的定义如下：
1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181...
为便于使用，计算机科学家还定义了一个额外的第0个斐波那契数字，其值为0。编写一
个函数来递归地计算第n个斐波那契数字。使用一个简单的程序来测试该函数，让用户决
定要计算多少个数字，然后逐个输出每个数字，并将每个数字显示在单独的一行中。
虽然斐波那契函数的朴素递归版本很优雅，几乎与其数学定义完全对应，但是执行速度很
慢。如果让计算机计算100个斐波那契数字，你会注意到随着n越来越大，计算速度越来越
慢。你是否能够重写这个函数来使用循环而不是递归？现在能够正确地计算多少个数字？
注意，在循环的每次迭代中，自然会想计算下一个数字。这只需要前两个数字。因此，没
有必要在一个vector<>中记录完整的序列。
*****************************************************************/
#include <iostream>
#include<chrono>//计时

long long fibonacci_recursive(size_t n);
long long fibonacci_iterative(size_t n);

int main()
{
    size_t count{};//要输出的斐波那契数字个数
    std::cout<<"要计算多少个斐波那契数?[0~92]:";
    std::cin>>count;

    //递归计算
    {auto start{std::chrono::high_resolution_clock::now()};//开始时间
    std::cout<<"\n递归版本结果：\n";
    for(size_t i{0};i<count;++i)
        std::cout<<"F("<<i<<") = "<<fibonacci_recursive(i)<<std::endl;
    auto end{std::chrono::high_resolution_clock::now()};//结束时间
    auto duration{std::chrono::duration_cast<std::chrono::milliseconds>(end-start)};
    std::cout<<"\n递归版本耗时："<< duration.count()<<" 毫秒。"<<std::endl;}

    //循环计算
    {auto start{std::chrono::high_resolution_clock::now()};//开始时间
    std::cout<<"\n循环版本结果：\n";
    for(size_t i{0};i<count;++i)
        std::cout<<"F("<<i<<") = "<<fibonacci_iterative(i)<<std::endl;
    auto end{std::chrono::high_resolution_clock::now()};//结束时间
    auto duration {std::chrono::duration_cast<std::chrono::microseconds>(end-start)};
    std::cout<<"\n循环版本耗时："<< duration.count()<<" 微秒。"<<std::endl;}

}

long long fibonacci_recursive(size_t n)
{
    if(n==0) return 0;
    if(n==1) return 1;
    //最后一个数等于前两个数相加，前两个数又分别用递归求得
    return fibonacci_recursive(n-1)+fibonacci_recursive(n-2);//最终只返回一个数
}

long long fibonacci_iterative(size_t n)
{
    if(n==0) return 0;
    if(n==1) return 1;

    long long prev2{0};
    long long prev1{1};
    long long current;

    for(size_t i{2};i<=n;++i)
    {
        current=prev1+prev2;
        prev2=prev1;
        prev1=current;
    }

    return current;
}