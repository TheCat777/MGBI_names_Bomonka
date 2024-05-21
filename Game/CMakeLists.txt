cmake_minimum_required(VERSION 3.21)

set(project "Game")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        Game.cpp)

set(${project}_HEADERS
        "Black hole.h" Button.h Constants.h Dialog.h Game.h MiniGame.h Parser.h Scene.h Sound.h Text.h Texture.h Kaleidoscope.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
