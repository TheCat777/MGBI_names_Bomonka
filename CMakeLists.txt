cmake_minimum_required(VERSION 3.21)

set(project_name "PTP")
project(${project_name})

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(lib/freetype2)

add_executable(${project_name} 
    main.cpp shader.h shader_m.h text.vs text.fs camera.h stb_image.h stb_image.cpp model.h mesh.h
    )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.3.9)
add_subdirectory(g-truc-glm-33b0eb9)
add_subdirectory(gladLib)

target_link_libraries(${project_name} GladLib glfw glm freetype.dll)
