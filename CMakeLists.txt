cmake_minimum_required(VERSION 3.30.0)
project("Dastardly Dungeon Dwellers" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

add_library(include Art.h Globals.h)
add_library(src Art.cpp Globals.cpp)

add_subdirectory(include)
add_subdirectory(src)

target_link_libraries("Dastardly Dungeon Dwellers" PUBLIC include)
target_link_libraries("Dastardly Dungeon Dwellers" PUBLIC src)

target_include_directories("Dastardly Dungeon Dwellers" PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include")
target_include_directories("Dastardly Dungeon Dwellers" PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")

include_directories(
        # Include
        "include"
        "include/Battle Controller"
        "include/Enemy"
        "include/Player"
        "include/Room Controller"

        # Source
        "src"
        "src/Battle Controller"
        "src/Enemy"
        "src/Player"
        "src/Room Controller"   
)

add_executable("Dastardly Dungeon Dwellers" "Dastardly Dungeon Dwellers.cpp")