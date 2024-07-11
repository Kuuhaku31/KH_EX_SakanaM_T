
cmake_minimum_required(VERSION 3.5.0)

# 设置项目名称
project(MyProject)

# 添加源文件
aux_source_directory(./src/system SYS)
set(SRC_FILES ./main.cpp)

# 添加头文件
include_directories(./include)

# 生成可执行文件
add_executable(run ${SRC_FILES} ${SYS})

# 忽略特定的编译器警告
target_compile_options(run PRIVATE -Wno-conversion-null)

# 链接到 EasyX 图形库
include_directories(./lib)

link_directories(./lib)

link_libraries(./lib/libeasyx.a)

# 如果库文件名和路径正确，尝试直接指定库文件的完整路径
target_link_libraries(run "${CMAKE_SOURCE_DIR}/lib/libeasyx.a")
