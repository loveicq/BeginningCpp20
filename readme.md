# C++20学习日志

1. 个人学习C++的小屋,使用教材为《C++20入门实践(第6版)》。  
2. 操作系统为windows10_x64,编辑器为vscode1.101.2版,编译器为mingw15.1.0。  
⏰gogoup!

**2025年7月23日**  
---
> *Ex1_01.cpp*  
```c++
#include <iostream>  
//书中import <iostream>语句在mingw15.1.0中会报错,需改用旧方法包含头文件

int main()
{
    int answer{42};
    std::cout << "The answer to life, the universe, and everything is "
              << answer
              << std::endl;
    std::cin.get(); //解决调试时CMD窗口一闪而过的问题

    return 0;
}
```
>🤞<span style=color:#DAF7A6>知识点:不同方式变量初始化的差别</span>  

|特性|int a = 10; (拷贝初始化)|int a{10}; (列表初始化)|
|:---|:---|---|
|窄化转换|允许（可能有警告）|禁止（编译错误）|
|类初始化效率|可能低效（需隐式转换）|高效（直接调用构造函数）|
|防止语法歧义|不能|能|
|C++标准|所有版本|C++11起支持|  

- 十进制数