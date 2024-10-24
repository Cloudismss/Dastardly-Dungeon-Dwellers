cmake_minimum_required(VERSION 3.30.0)
project(Dastardly-Dungeon-Dwellers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

# executable
add_executable(${PROJECT_NAME} "Dastardly Dungeon Dwellers.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Dastardly Dungeon Dwellers")

# dirs
add_subdirectory(include)
add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} src)

# fmt library
add_subdirectory(lib/fmt)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

# boost library
#add_subdirectory(lib/boost EXCLUDE_FROM_ALL)
#target_link_libraries(${PROJECT_NAME} Boost::random)