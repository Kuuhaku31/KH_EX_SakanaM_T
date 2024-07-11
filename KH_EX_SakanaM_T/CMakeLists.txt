
cmake_minimum_required(VERSION 3.5.0)

# 设置项目名称
project(MyProject)

# 添加源文件
aux_source_directory(./src SRC_SUB)
aux_source_directory(. SRC_CUR)

# 添加头文件
include_directories(./include)

# 生成可执行文件
add_executable(run ${SRC_SUB} ${SRC_CUR}) 

# 链接到 EasyX 图形库
link_directories(./lib)
target_link_libraries(run libeasyx.a)
