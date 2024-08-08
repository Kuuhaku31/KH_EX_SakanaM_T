
cmake_minimum_required(VERSION 3.5)
project(SakanaT
    VERSION 0.0.1
    DESCRIPTION "a demo for sakana"

    # HOMEPAGE_URL "https://github.com/Kuuhaku31/cmake_planning_test"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置共享库（DLL）的输出目录
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置静态库的输出目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置文件目录
set(GAME_BASE ${PROJECT_SOURCE_DIR}/src/game_base)
set(GAME_OBJECT ${PROJECT_SOURCE_DIR}/src/game_object)
set(GAME_FACTORY ${PROJECT_SOURCE_DIR}/src/game_factory)
set(GAME_SYSTEM ${PROJECT_SOURCE_DIR}/src/game_system)

# 添加子目录
add_subdirectory(src)
