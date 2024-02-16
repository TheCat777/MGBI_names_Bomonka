cmake_minimum_required(VERSION 3.21)

set(project_name "GladLib")

add_library(GladLib STATIC include/glad/glad.h src/glad.c)
target_include_directories(GladLib PUBLIC include/)
