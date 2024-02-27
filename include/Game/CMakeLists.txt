cmake_minimum_required(VERSION 3.21)

set(project "Game")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES game.cpp stb_image.cpp)

set(${project}_HEADERS game.h stb_image.h shader_s.h)

set(${project}_SOURCE_LIST ${${project}_SOURCES} ${${project}_HEADERS})

add_library(${project} STATIC ${${project}_SOURCE_LIST})