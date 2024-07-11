cmake_minimum_required(VERSION 3.5.0)

project(Sakana VERSION 0.1.0 LANGUAGES C CXX)

# 添加所有相关的源文件到可执行文件中
add_executable (run main.cpp src/GameManager.cpp) 
# 添加其他需要的源文件

# 设置头文件的搜索路径
target_include_directories(run PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 假设 EasyX 库文件位于 E:/EasyX/lib 目录下，并且库文件名为 libeasyx.a
# 首先，指定库文件的搜索路径
link_directories(D:/杂/ex/lib64)

# 然后，链接库到你的项目
target_link_libraries(run libeasyx.a)
