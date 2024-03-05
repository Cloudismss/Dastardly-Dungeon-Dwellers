cmake_minimum_required(VERSION 3.26)
project(Dastardly_Dungeon_Dwellers)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(Dastardly_Dungeon_Dwellers
        "Dastardly Dungeon Dwellers.cpp"
        "Dastardly Dungeon Dwellers.h"
        Art.cpp
        Art.h
        Enemy.cpp
        Enemy.h
        Progression.cpp
        Progression.h
)