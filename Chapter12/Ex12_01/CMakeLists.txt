# Chapter12/Ex12_01/CMakeLists.txt

# 获取目标名称
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 收集所有 .cpp 文件（非模块文件）
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# 收集所有 .cppm 模块接口文件（用 FILE_SET 方式处理）
file(GLOB MODULE_SOURCES CONFIGURE_DEPENDS "*.cppm")

# 检查是否有源文件
list(LENGTH SOURCES SOURCE_COUNT)
list(LENGTH MODULE_SOURCES MODULE_COUNT)

if(SOURCE_COUNT EQUAL 0 AND MODULE_COUNT EQUAL 0)
    message(WARNING "目录 ${CMAKE_CURRENT_SOURCE_DIR} 中没有找到任何源文件，跳过构建。")
    return()
endif()

# 创建可执行目标
add_executable(${TARGET_NAME})

# 添加普通源文件
if(SOURCE_COUNT GREATER 0)
    target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
endif()

# 添加模块文件（关键：使用 FILE_SET CXX_MODULES）
if(MODULE_COUNT GREATER 0)
    target_sources(${TARGET_NAME}
        PRIVATE
            ${MODULE_SOURCES}
        PUBLIC
            FILE_SET CXX_MODULES
            FILES ${MODULE_SOURCES}
    )
endif()

# 设置输出目录
set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# 头文件搜索路径
target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "    - 目标: ${TARGET_NAME} (${SOURCE_COUNT} 个 .cpp, ${MODULE_COUNT} 个 .cppm)")