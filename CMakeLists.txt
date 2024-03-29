cmake_minimum_required(VERSION 3.21)

set(project_name "MGBI_Bomonka")

project(${project_name} LANGUAGES CXX)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/sfml-src/include)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/sfml-build/lib)


add_executable(${project_name} main.cpp)

add_subdirectory(Game)

target_link_libraries(${project_name} sfml-graphics sfml-audio)
target_link_libraries(${project_name} Game)
target_compile_features(${project_name} PRIVATE cxx_std_17)
if(WIN32)
    add_custom_command(
            TARGET ${project_name}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${project_name}>
            VERBATIM)
endif()
install(TARGETS ${project_name})
