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

- [x] 完成 Markdown 学习
- [ ] 上传文件到 Gitee
- [ ] 创建第一个仓库