# 1. 设置 CMake 最低版本要求
# C++20 Modules 的官方支持在 3.28 版本才趋于稳定，建议保持这个版本或更高。
cmake_minimum_required(VERSION 3.28)

# 2. 定义项目名称和语言
# 这里我们告诉 CMake 这是一个 C++ 项目。
project(Ex12_17A LANGUAGES CXX)

# 3. 强制开启 C++20 标准
# 这一点至关重要，因为 .cppm 文件必须使用 C++20 或更新的标准才能编译。
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 如果编译器不支持 C++20，直接报错而不是降级

# 4. 创建可执行文件目标
# 我们将生成的程序命名为 Ex12_17A (你可以改成自己喜欢的名字)。
# 在这里列出所有的源文件 (.cpp) 和模块接口文件 (.cppm)。
add_executable(Ex12_17A
    Ex12_17.cpp           # [主程序] 包含 main() 函数的入口文件
    
    # --- 模块接口文件 (.cppm) ---
    # CMake 会自动扫描这些文件的 module 声明来构建依赖图。
    
    Box.cppm              # [模块 box] 定义 Box 类的基础接口
    RandomBoxes.cppm      # [模块 box.random] 生成随机盒子的子模块
    SharedBox.cppm        # [单元 truckload:shared_box] 定义 SharedBox 别名
    Package.cppm          # [单元 truckload:package] 定义链表节点 Package
    Truckload.cppm        # [模块 truckload] 导出 Truckload 类的主接口
    Truckload-impl.cpp    # [实现文件] 注意后缀是 .cpp，包含 Truckload 的具体函数实现
)

# 5. 针对 MSVC (Visual Studio) 的特殊优化配置
# 如果你使用的是 Visual Studio 2022 (MSVC 编译器)，这段代码能显著提升模块编译速度。
if(MSVC)
    # /experimental:module 开启实验性模块支持（VS2022 目前仍需此标志）
    # /std:c++latest 启用最新的 C++ 特性支持
    target_compile_options(Ex12_17A PRIVATE /experimental:module /std:c++latest)
endif()