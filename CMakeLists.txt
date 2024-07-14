cmake_minimum_required(VERSION 3.30.0)
project(Dastardly-Dungeon-Dwellers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(${PROJECT_NAME} "Dastardly Dungeon Dwellers.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Dastardly Dungeon Dwellers")
target_link_libraries(${PROJECT_NAME} src)
target_link_libraries(${PROJECT_NAME} include)
add_subdirectory(src)
add_subdirectory(include)