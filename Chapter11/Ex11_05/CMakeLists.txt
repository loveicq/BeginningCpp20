# ============================================================
#  通用 CMakeLists.txt 模板 —— 适用于任意 ExXX_XX 案例目录
#  自动检测当前目录下的 .cppm 模块文件和 .cpp 源文件
#  无需修改即可用于其他案例（只需复制到对应目录）
# ============================================================
cmake_minimum_required(VERSION 3.28)

# ---------- 项目名 = 当前文件夹名（自动获取，无硬编码） ----------
get_filename_component(PROJECT_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

# ---------- C++20 标准 ----------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------- 自动收集源文件 ----------
file(GLOB MODULE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cppm")
file(GLOB CPP_FILES    CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# ---------- 创建可执行目标 ----------
add_executable(${PROJECT_NAME})

# 模块接口/分区文件 → FILE_SET CXX_MODULES（CMake 自动处理依赖顺序）
if(MODULE_FILES)
    target_sources(${PROJECT_NAME} PRIVATE
        FILE_SET CXX_MODULES
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
        FILES ${MODULE_FILES}
    )
endif()

# 普通 .cpp 文件（模块实现单元 + main）
if(CPP_FILES)
    target_sources(${PROJECT_NAME} PRIVATE ${CPP_FILES})
endif()

# ---------- 可选：链接额外库（按需取消注释） ----------
# target_link_libraries(${PROJECT_NAME} PRIVATE some_lib)