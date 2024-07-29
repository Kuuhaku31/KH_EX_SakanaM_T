
project(main_planning)

# 添加子目录
add_subdirectory(game_base)
add_subdirectory(game_object)
add_subdirectory(game_system)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 添加头文件
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_BASE} ${GAME_OBJECT} ${GAME_SYSTEM})

# 添加链接库
target_link_libraries(${PROJECT_NAME} game_base game_object game_system)
