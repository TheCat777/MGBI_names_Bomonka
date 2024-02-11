cmake_minimum_required(VERSION 3.21)
project(black_hole)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

link_directories(lib)


add_executable(${PROJECT_NAME} main.cpp glfw3.dll)

target_link_libraries(${PROJECT_NAME} glfw3.dll libglfw3.a libglfw3dll.a)

