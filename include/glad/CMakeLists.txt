cmake_minimum_required(VERSION 3.21)

set(project "glad")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        glad.cpp)

set(${project}_HEADERS
        glad.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
