cmake_minimum_required(VERSION 3.21)

set(project_name "MGBI_Bomonka")
project(${project_name})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-static-libstdc++ -static-libgcc")

include_directories(include)
link_directories(lib/freetype2)

add_executable(${project_name} 
    main.cpp
    )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(include/glfw-3.3.9)
add_subdirectory(include/g-truc-glm-33b0eb9)
add_subdirectory(include/gladLib)
add_subdirectory(include/Game)

target_link_libraries(${project_name} GladLib glfw glm freetype.dll Game)
