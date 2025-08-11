// 试验宽字符输入输出,在控制台,输入相当麻烦,未解决
#include <iostream>
#include <format>
#include <stdio.h>

int main()
{
    using namespace std;

    char c{'A'};
    char32_t wc = U'Ω'; // UTF-32字符

    // 全部使用cout和UTF-8输出
    cout << format("c='{}', size={}\n", c, sizeof(c));
    cout << format("wc=U+{:04X},size={}\n", static_cast<uint32_t>(wc), sizeof(wc));

    return 0;
}