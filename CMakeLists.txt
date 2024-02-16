cmake_minimum_required(VERSION 3.21)
project(black_hole)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
link_directories(lib)
link_directories(lib/Release/x64)

set(${PROJECT_NAME}_SOURCES main.cpp)

set(${PROJECT_NAME}_SOURCE_LIST ${${PROJECT_NAME}_SOURCES})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_LIST} main.cpp)

target_link_libraries(${PROJECT_NAME} glew32.lib glfw3.dll libglfw3.a libglfw3dll.a)

