// 针对Deepseek说std::round()采用银行家舍入法进行测试,结果表明Ds的说法是错误的
#include <iostream>
#include <cmath>
int main()
{
    using namespace std;
    cout << "round(3.5) = " << round(3.5) << endl; // 结果等于4
    cout << "round(4.5) = " << round(4.5) << endl; // 结果等于5

    return 0;
}