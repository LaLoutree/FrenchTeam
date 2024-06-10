cmake_minimum_required(VERSION 3.16)

project(bomberman)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

find_package(raylib 4.0 QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz)
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

include_directories(bomberman include)

add_executable(bomberman src/Main.cpp
    src/Game/Engine.cpp
    src/Game/Loop/Display/Menu.cpp
    src/Game/Object/Platform/Bombs/BombManager.cpp
    src/Game/Object/Platform/Bombs/Bomb.cpp
    src/Game/Object/Platform/Map/Map.cpp
    src/Game/Object/Character/Player.cpp)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if(CMAKE_SYSTEM MATCHES Windows)
#    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
#    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
#    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
#    target_link_libraries(${PROJECT_NAME} raylib)
    set(OS WINDOWS)
    set(CMAKE_CXX_COMPILER "C:/Program Files/mingw64/bin/g++.exe" )
    set(CMAKE_C_COMPILER "C:/Program Files/mingw64/bin/gcc.exe" )
    set(CMAKE_CXX_FLAGS "-std=c++20")
endif()