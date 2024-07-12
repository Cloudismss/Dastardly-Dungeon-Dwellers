cmake_minimum_required(VERSION 3.26)
project(Dastardly_Dungeon_Dwellers)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(Dastardly_Dungeon_Dwellers

        # Main
        "Dastardly Dungeon Dwellers.cpp"
        "Dastardly Dungeon Dwellers.h"

        # Include
        "include/Art.h"
        "include/Enemy.h"
        "include/Progression.h"

        # Source
        "src/Art.cpp"
        "src/Enemy/Enemy.cpp"
        "src/Progression.cpp"     
)