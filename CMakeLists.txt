cmake_minimum_required(VERSION 3.31.0)
project(Dastardly-Dungeon-Dwellers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch fmt library
include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG main
)
FetchContent_MakeAvailable(fmt)

# Make target - 'run' - compiles and runs the produced binary
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Executable
add_executable(${PROJECT_NAME} "src/DastardlyDungeonDwellers.cpp" "res/DDD.rc")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Dastardly Dungeon Dwellers")

# Dirs
add_subdirectory(include)
add_subdirectory(src)

# Libraries
target_link_libraries(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} src)
target_link_libraries(src fmt::fmt)
