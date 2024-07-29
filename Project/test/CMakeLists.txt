
# cmake_minimum_required(VERSION 3.5.0)

# # 设置项目名称
# project(MyProject)

# # 设置TDM-GCC-64编译器路径
# set(CMAKE_C_COMPILER "E:/Microsoft VS Code/TDM-GCC-64/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER "E:/Microsoft VS Code/TDM-GCC-64/bin/g++.exe")

# # 添加源文件
# # 查找并包含src目录下的全部源文件
# file(GLOB_RECURSE SRC_FILES src/*.cpp)

# set(MAIN ./main.cpp)

# # 添加头文件
# include_directories(./include/base/)
# include_directories(./include/object/)
# include_directories(./include/system/)

# # 打印找到的源文件列表（可选）
# message(STATUS "Source files: ${SRC_FILES}")

# # 生成可执行文件
# add_executable(run ${MAIN} ${SRC_FILES})

# # 忽略特定的编译器警告
# target_compile_options(run PRIVATE -Wno-conversion-null)

# # 链接到 EasyX 图形库
# include_directories(./lib)
# link_directories(./lib)
# link_libraries(./lib/libeasyx.a)

# # 如果库文件名和路径正确，尝试直接指定库文件的完整路径
# target_link_libraries(run "${CMAKE_SOURCE_DIR}/lib/libeasyx.a")
