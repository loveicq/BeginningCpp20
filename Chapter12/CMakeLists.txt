# ============================================================
# Chapter12/CMakeLists.txt - 章节级总控文件
# 作用：自动发现本目录下的所有子目录，只添加有 .cpp/.cppm 文件的案例
# ============================================================

# 自动发现当前目录下的所有子目录
file(GLOB SUB_DIRS CONFIGURE_DEPENDS "*")

# 排除不需要添加的目录
set(EXCLUDED_DIRS 
    "bin"
    "build"
    ".vscode"
    ".git"
    "CMakeFiles"
)

list(SORT SUB_DIRS)

foreach(SUB_DIR ${SUB_DIRS})
    if(IS_DIRECTORY ${SUB_DIR})
        get_filename_component(DIR_NAME ${SUB_DIR} NAME)
        
        # 检查是否需要排除
        set(SKIP FALSE)
        foreach(EXCLUDED ${EXCLUDED_DIRS})
            if(${DIR_NAME} STREQUAL ${EXCLUDED})
                set(SKIP TRUE)
                break()
            endif()
        endforeach()
        
        if(NOT SKIP)
            # 检查该案例目录下是否有源文件（.cpp 或 .cppm）
            file(GLOB CHECK_SOURCES "${SUB_DIR}/*.cpp" "${SUB_DIR}/*.cppm")
            list(LENGTH CHECK_SOURCES SOURCE_COUNT)
            
            if(SOURCE_COUNT GREATER 0)
                message(STATUS "  - 发现案例/练习: ${DIR_NAME} (${SOURCE_COUNT} 个源文件)")
                add_subdirectory(${DIR_NAME})
            else()
                message(STATUS "  - 跳过空案例/练习: ${DIR_NAME} (暂无源文件)")
            endif()
        endif()
    endif()
endforeach()