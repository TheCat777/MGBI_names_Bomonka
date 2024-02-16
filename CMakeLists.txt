cmake_minimum_required(VERSION 3.21)

set(project_name "PTP")
project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_executable(${project_name} 
    main.cpp 
    
    )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.3.9)
target_link_libraries(${project_name} glfw)

add_subdirectory(gladLib)
target_link_libraries(${project_name} GladLib)