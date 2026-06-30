# ============================================================
# cpp20/CMakeLists.txt - 根目录总控文件
# 作用：自动发现所有 Chapter* 目录，只添加包含 CMakeLists.txt 的章节
# ============================================================

cmake_minimum_required(VERSION 3.28)
project(Cpp20Modules VERSION 1.0.0)

# 添加这一行：生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------- 全局设置 --------------------
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启 C++20 模块实验性支持
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0.9.0" CACHE STRING "Enable experimental import std support")

# 全局编译选项（所有子目录自动继承）
add_compile_options(
    -fmodules-ts
    # -fmodule-mapper
    -g                           # 生成调试信息
    -Wall                        # 开启所有警告
)

# -------------------- 自动发现所有章节 --------------------
# 使用 GLOB 匹配当前目录下所有以 Chapter 开头的目录
file(GLOB CHAPTER_DIRS CONFIGURE_DEPENDS "Chapter*")

# 排序，保证构建顺序稳定（可选）
list(SORT CHAPTER_DIRS)

# 遍历每个章节目录
foreach(CHAPTER_DIR ${CHAPTER_DIRS})
    if(IS_DIRECTORY ${CHAPTER_DIR})
        # 检查该目录下是否有 CMakeLists.txt
        if(EXISTS "${CHAPTER_DIR}/CMakeLists.txt")
            message(STATUS "✅ 发现并加载章节: ${CHAPTER_DIR}")
            add_subdirectory(${CHAPTER_DIR})
        else()
            # 没有 CMakeLists.txt，跳过该章节
            message(STATUS "⏭️  跳过章节: ${CHAPTER_DIR} (没有 CMakeLists.txt)")
        endif()
    endif()
endforeach()

# -------------------- 打印提示信息 --------------------
message(STATUS "========================================")
message(STATUS "所有章节已加载完成。")
message(STATUS "使用 'cmake --build . --target <目标名>' 编译指定案例")
message(STATUS "例如: cmake --build . --target Ex12_01")
message(STATUS "========================================")