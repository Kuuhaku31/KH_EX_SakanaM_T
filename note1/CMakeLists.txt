
cmake_minimum_required(VERSION 3.5.0)

# 设置项目名称
project(MyProject)

# 添加源文件
# 查找并包含src目录下的全部源文件
file(GLOB_RECURSE SRC_FILES ../KH_EX_SakanaM_T/src/*.cpp)

set(MAIN ./main.cpp)

# 添加头文件
include_directories(../KH_EX_SakanaM_T/include/base/)
include_directories(../KH_EX_SakanaM_T/include/object/)
include_directories(../KH_EX_SakanaM_T/include/system/)

# 打印找到的源文件列表（可选）
message(STATUS "Source files: ${SRC_FILES}")

# 生成可执行文件
add_executable(run ${MAIN} ${SRC_FILES} ${SYS} ${BASE} ${OBJ})

# 忽略特定的编译器警告
target_compile_options(run PRIVATE -Wno-conversion-null)

# 链接到 EasyX 图形库
include_directories(../KH_EX_SakanaM_T/lib)
link_directories   (../KH_EX_SakanaM_T/lib)
link_libraries     (../KH_EX_SakanaM_T/lib/libeasyx.a)

# 如果库文件名和路径正确，尝试直接指定库文件的完整路径
target_link_libraries(run "${CMAKE_SOURCE_DIR}/../KH_EX_SakanaM_T/lib/libeasyx.a")
