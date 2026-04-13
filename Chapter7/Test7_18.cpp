// 测试wchar_t字符串
#include <iostream>
#include <string>

int main()
{
    std::wstring saying{L"Test!"};     // 定义使用wstring,赋值使用"L"
    std::wcout << saying << std::endl; // 使用wcout输出
}