cmake_minimum_required(VERSION 3.30.0)
project(Dastardly-Dungeon-Dwellers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable static compilation
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# fmt library
include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

if (CMAKE_HOST_WIN32)
  # Set clang compiler
  set(CMAKE_C_COMPILER clang)
  set(CMAKE_CXX_COMPILER clang++)

  # UTF-8 option is required when using fmt
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# Executable
add_executable(${PROJECT_NAME} "src/DastardlyDungeonDwellers.cpp" "res/DDD.rc")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Dastardly Dungeon Dwellers")

# Dirs
add_subdirectory(include)
add_subdirectory(src)
target_link_libraries(${PROJECT_NAME} include)
target_link_libraries(${PROJECT_NAME} src)

# fmt library
target_link_libraries(src fmt::fmt)
